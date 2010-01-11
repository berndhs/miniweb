#!/bin/sh

PROGRAM=miniweb

DEST=/usr/local/bin

install --compare $PROGRAM $DEST

ls -l $DEST/$PROGRAM
