#!/usr/bin/python

#pylint: disable=I0011,C0111

import elftools.elf
import argparse


def argumentProcessing():
    parse = argparse.ArgumentParser()
    parse.add_argument("-f", "--file", required=True,
                       help="File to parse")
    return parse.parse_args()


def main():
    opt = argumentProcessing()
    print "Hello %s" % opt.file

if __name__ == "__main__":
    main()
