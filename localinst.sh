#!/bin/sh

PROGRAM=miniweb

DEST=$HOME/bin

install --strip $PROGRAM $DEST

ls -l $DEST/$PROGRAM
