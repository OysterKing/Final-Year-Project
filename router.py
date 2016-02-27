
from mininet.node import Switch
from mininet.util import (quietRun, errRun, errFail, moveIntf, isShellBuiltin,
                           numCores, retry, mountCgroups)
from mininet.moduledeps import moduleDeps, pathCheck, OVS_KMOD, OF_KMOD, TUN
from mininet.link import Link, Intf, TCIntf
from mininet.log import info, error, warn, debug


class Router(Switch):
    "Bridge switch."

    def __init__(self, name, **params):
        super(Router, self).__init__(name, **params)

    @classmethod
    def setup(cls):
	return True

    def dpctl(self, *args):
        return True

    def attach(self, intf):
        "Connect a data port to the bridge"
        self.cmd('ifconfig', intf, 'up')
        self.TCReapply(intf)

    def detach(self, intf):
        "Disconnect a data port"
        self.cmd('ifconfig', intf, down)

    def deleteIntfs(self, checkName=True):
        super(Router, self).deleteIntfs()

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
        self.cmd('ifconfig', self, 'up')

    def stop(self):
        "Terminate OVS switch."
        self.cmd('ifconfig', self, 'down')
        self.deleteIntfs()
