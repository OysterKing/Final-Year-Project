from mininet.node import Switch
from mininet.util import (quietRun, errRun, errFail, moveIntf, isShellBuiltin,
                           numCores, retry, mountCgroups)
from mininet.moduledeps import moduleDeps, pathCheck, OVS_KMOD, OF_KMOD, TUN
from mininet.link import Link, Intf, TCIntf
from mininet.log import info, error, warn, debug


class BridgeSwitch(Switch):
    "Bridge switch."

    def __init__(self, name, blocking=False, **params):
        Switch.__init__(self, name, **params)
        self.block = blocking

    @classmethod
    def setup(cls):
        pathCheck('brctl', moduleName='Bridge Control')
        pathCheck('ebtables', moduleName='Ethernet filter')

    def dpctl(self, *args):
        return True

    def attach(self, intf):
        "Connect a data port to the bridge"
        self.cmd('brctl addif', self, intf)
        self.cmd('ifconfig', intf, 'up')
        if self.block:
            self.cmd('ebtables -A FORWARD -i', intf, '-p ARP -j DROP')
        self.TCReapply(intf)

    def detach(self, intf):
        "Disconnect a data port"
        self.cmd('brctl delif', self, intf)

    def deleteIntfs(self, checkName=True):
        for intf in self.intfs.values():
            if self.block:
                self.cmd('ebtables -D FORWARD -i', intf, '-p ARP -j DROP')
        super(BridgeSwitch, self).deleteIntfs()

    def controllerUUIDs(self):
        "Return ovsdb UUIDs for our controllers"
        uuids = []
        return uuids

    def connected(self):
        return True

    @staticmethod
    def TCReapply(intf):
        if type(intf) is TCIntf:
            intf.config(**intf.params)

    def start(self, controllers):
        self.cmd('ifconfig lo up')
        self.cmd('ifconfig', self, 'down')
        self.cmd('brctl delbr', self)
        self.cmd('brctl addbr', self)
        for intf in self.intfList():
            if not intf.IP():
                self.attach(intf)
        self.cmd('ifconfig', self, 'up')

    def stop(self):
        "Terminate OVS switch."
        self.cmd('ifconfig', self, 'down')
        self.cmd('brctl delbr', self)
        self.deleteIntfs()

