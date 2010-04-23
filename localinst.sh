#!/bin/sh

PROGRAM=miniweb

DEST=$HOME/bin

install -s -p $PROGRAM $DEST

ls -l $DEST/$PROGRAM
