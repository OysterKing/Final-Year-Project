import sys
import random
import socket
import struct

try:
    from mininet.topo import Topo

    class SingleSwitchTopo(Topo):

        def __init__(self, n=2, name="s1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            switch = self.addSwitch(name, blocking=blocking)
            
            
            for h in range(n):
                host = self.addHost('h%s' % (h + 1))
                self.addLink(host, switch, **link_opts)


    class SwitchRouterSwitchTopo(Topo):

        def __init__(self, n=2, name="r1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            switch1 = self.addSwitch('s1')
            router1 = self.addSwitch('r1')
            switch2 = self.addSwitch('s2')
            
            for h in range(n):
                host = self.addHost('net1-h%s' % (h + 1))
                self.addLink(host, switch1, **link_opts)

            for h in range(n):
                host = self.addHost('net2-h%s' % (h + 1))
                self.addLink(host, switch2, **link_opts)

            self.addLink(switch1,router1,**link_opts)
            self.addLink(switch2,router1,**link_opts)

    class SwitchRouterSwitchBadLinkTopo(Topo):

        def __init__(self, n=2, name="r1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            switch1 = self.addSwitch('s1')
            router1 = self.addSwitch('r1')
            switch2 = self.addSwitch('s2')
            
            client = self.addHost('hostA')
            self.addLink(client, switch1, **link_opts)

            server = self.addHost('hostB')
            self.addLink(server, switch2, **link_opts)

            self.addLink(switch1,router1,**link_opts)
            self.addLink(switch2,router1, bw=0.1, delay=10, loss=3, max_queue_size=100, use_htb=True)


    class ClientRouterServerTopo(Topo):

        def __init__(self, n=2, name="r1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            router = self.addSwitch('router1')
            
            client = self.addHost('hostA')
            self.addLink(client, router, **link_opts)

            server = self.addHost('hostB')
            self.addLink(server, router, **link_opts)

    class ClientRouterRouterServerTopo(Topo):

        def __init__(self, n=2, name="r1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            router1 = self.addSwitch('router1')
            router2 = self.addSwitch('router2')
            
            client = self.addHost('hostA')
            self.addLink(client, router1, **link_opts)

            server = self.addHost('hostB')
            self.addLink(server, router2, **link_opts)
            # self.addLink(router1, router2, **link_opts)
            # bad_link_opts = {"bw":1 , "delay": 0, "loss": 0, "use_htb": False}
            # self.addLink(router1, router2, bw=1, delay=0, loss=0)



    class FourNetsTopo(Topo):

        def __init__(self, n=3, name="r1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            switch1 = self.addSwitch('s1')
            switch2 = self.addSwitch('s2')
            switch3 = self.addSwitch('s3')
            switch4 = self.addSwitch('s4')
            router1 = self.addSwitch('r1')
            
            for h in range(n):
                host = self.addHost('net1-h%s' % (h + 1))
                self.addLink(host, switch1, **link_opts)

            for h in range(n):
                host = self.addHost('net2-h%s' % (h + 1))
                self.addLink(host, switch2, **link_opts)

            for h in range(n):
                host = self.addHost('net3-h%s' % (h + 1))
                self.addLink(host, switch3, **link_opts)

            for h in range(n):
                host = self.addHost('net4-h%s' % (h + 1))
                self.addLink(host, switch4, **link_opts)

            self.addLink(switch1,router1,**link_opts)
            self.addLink(switch2,router1,**link_opts)
            self.addLink(switch3,router1,**link_opts)
            self.addLink(switch4,router1,**link_opts)

    class ThreeNetsTopo(Topo):

        def __init__(self, n=3, name="r1", blocking=False, link_opts={}, **opts):
            Topo.__init__(self, **opts)
            switch1 = self.addSwitch('s1')
            switch2 = self.addSwitch('s2')
            switch3 = self.addSwitch('s3')
            router1 = self.addSwitch('r1')

            for h in range(n):
                host = self.addHost('net1-h%s' % (h + 1))
                self.addLink(host, switch1, **link_opts)

            for h in range(n):
                host = self.addHost('net2-h%s' % (h + 1))
                self.addLink(host, switch2, **link_opts)

            for h in range(n):
                host = self.addHost('net3-h%s' % (h + 1))
                self.addLink(host, switch3, **link_opts)

            self.addLink(switch1,router1,**link_opts)
            self.addLink(switch2,router1,**link_opts)
            self.addLink(switch3,router1,**link_opts)


except ImportError:
    pass

def random_ips(count, subnet=24):
    assert subnet <= 32, "Network must be smaller equal 32"
    assert subnet > 0, "Network must be larger than zero"

    max_size = 2 ** (32 - subnet) - 2
    if count > max_size:
        sys.stderr.write("random_ips cannot generate more than {1} unique ip addresses. You requested {0}\n".format(count, max_size))
        sys.exit(1)

    ips = []
    prefix = 0

    prefix_random = random.randint(1, (2**32) - 2)

    prefix = ((0x01000000 | prefix_random) & 0xc8ffffff) & ( ~((2 << 32 - subnet - 1) - 1) & 0xFFFFFFFF)  # pad 
    prefix = (0x01000000 | prefix)

    while len(ips) != count:

        ip = random.randint(10,  2**(32 - subnet) - 2)  # make sure we don't get the broadcast address

        if ip and ip not in ips:
            ips.append(ip) 

    return map(lambda x: "{0}/{1}".format(prefix + x, subnet), ips)

def random_subnet(subnet=24):
    assert subnet <= 32, "Network must be smaller equal 32"
    assert subnet > 0, "Network must be larger than zero"

    max_size = 2 ** (32 - subnet) - 2

    # offset_ip = 0 # in case we want to set this to a router 
    prefix = 0

    prefix_random = random.randint(1, (2**32) - 2)

    prefix = ((0x01000000 | prefix_random) & 0xc8ffffff) & ( ~((2 << 32 - subnet - 1) - 1) & 0xFFFFFFFF)  # pad 
    prefix = (0x01000000 | prefix)
    # print prefix 
    # print "{0}/{1}".format(prefix, subnet)
    return prefix, subnet

def random_macs(count):
    result = []
    while len(result) != count:
        mac = random.randint(1, 281474976710655) 
        if not mac in result:
            result.append(mac)

    return result

def random_link_bw():
    return random.randint(1,5)

def random_link_loss():
    return random.randint(1,3)

def random_link_delay():
    return str(random.randint(2,10)) + "ms"

def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: {0} birthday\n".format(sys.argv[0]))
        sys.exit(1)

    random.seed(int(sys.argv[1]))
    result = random_subnet(24)
    print result

if __name__ == '__main__':
    main()

