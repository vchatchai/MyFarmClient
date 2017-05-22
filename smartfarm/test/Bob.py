from pyp2p.net import *

from pyp2p.unl import UNL
from pyp2p.dht_msg import DHT
#Setup Bob's p2p node.
#bob = Net(passive_bind="192.168.0.44", passive_port=44445, interface="eth0:1", node_type="passive", debug=1)
#bob = Net(passive_port=44445, node_type="passive", debug=1)
bob_dht = DHT()
bob = Net(passive_bind="192.168.1.105", passive_port=44445, interface="en1", node_type="passive",dht_node=alice_dht, debug=1)
bob.start()
bob.bootstrap()
bob.advertise()

#Event loop.
while 1:
    for con in bob:
        con.send_line("test")

    time.sleep(1)