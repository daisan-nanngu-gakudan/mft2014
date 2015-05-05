#!/bin/bash

./dscan.py > finderItemsPosition.txt
cp -p finderItemsPosition.txt ../10_Controller/bin/data/finderItems_new.txt

# 以下は旧バージョン時のもの
#/tmp/dscan.dst/usr/local/bin/dscan > finderItemsPosition.txt
#cp -p finderItemsPosition.txt ../10_Controller/bin/data/finderItems_new.txt