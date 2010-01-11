#!/bin/sh

ARCHIVE=$1
BRANCH=$2
TARFILE=$ARCHIVE.tar.gz

git archive --prefix=$ARCHIVE/ $BRANCH | gzip > $TARFILE

ls -l $TARFILE
