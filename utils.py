import re
from subprocess import Popen

from mininet.log import error
from mininet.util import quietRun
import datetime

import os
DEVNULL = open(os.devnull, 'wb')


def get_seed(seed):
    return seed * datetime.datetime.now().timetuple().tm_yday 

def quoteArg( arg ):
    "Quote an argument if it contains spaces."
    return repr( arg ) if ' ' in arg else arg

def makeTerm( node, title='Node', term='xterm' ):
    """Run screen on a node, and hook up a terminal.
       node: Node object
       title: base title
       term: 'xterm' or 'gterm'
       returns: process created"""
    title += ': ' + node.name
    if not node.inNamespace:
        title += ' (root)'
    cmds = {
        'xterm': [ 'xterm', '-title', title, '-e' ],
        'xfce': [ 'xfce4-terminal', '--title', title, '-e' ],
        'gterm': [ 'gnome-terminal', '--title', title, '-e' ]
    }
    if term not in cmds:
        error( 'invalid terminal type: %s' % term )
        return
    if not node.execed:
        node.cmd( 'screen -dmS ' + 'mininet.' + node.name)
        args = [ 'screen', '-D', '-RR', '-S', 'mininet.' + node.name ]
    else:
        args = [ 'sh', '-c', 'exec tail -f /tmp/' + node.name + '*.log' ]
    if term == 'gterm' or term=='xfce':
        # Compress these for gnome-terminal, which expects one token
        # to follow the -e option
        args = [ ' '.join( [ quoteArg( arg ) for arg in args ] ) ]
    print cmds[ term ] + args
    return Popen( cmds[ term ] + args, stdout = DEVNULL, stderr = DEVNULL)

def makeTabbedTerm( nodes, orig_title='Node', term='xterm' ):
    """Run screen on a node, and hook up a terminal.
        node: Node object
        title: base title
        term: 'xterm' or 'gterm'
        returns: process created"""

    cmds = {
        'xfce': [ 'xfce4-terminal',  ]
    }
    cmd = []

    for index, node in enumerate(nodes):
        title = orig_title
        title += ': ' + node.name
        if not node.inNamespace:
            title += ' (root)'


        if index != 0:
            cmds[term].append('--tab')
        cmds[term].append('--title')
        cmds[term].append('{0}'.format(title))

        if term not in cmds:
            error( 'invalid terminal type: %s' % term )
            return

        if not node.execed:
            node.cmd( 'screen -dmS ' + 'mininet.' + node.name)
            args = [ '-e',  'screen -D -RR -S mininet.{0}'.format(node.name )]
        else:
            args = [ 'sh', '-c', 'exec tail -f /tmp/' + node.name + '*.log' ]

        cmds[term] += args

    return [ Popen( cmds[ term ], stdout = DEVNULL, stderr = DEVNULL)]

def makeTerms( nodes, title='Node', term='xterm' ):
    """Create terminals.
       nodes: list of Node objects
       title: base title for each
       returns: list of created terminal processes"""
    return [ makeTerm( node, title, term ) for node in nodes ]
