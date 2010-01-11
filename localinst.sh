#!/bin/sh

PROGRAM=miniweb

DEST=$HOME/bin

install --compare $PROGRAM $DEST

ls -l $DEST/$PROGRAM
