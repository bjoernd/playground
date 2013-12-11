#!/usr/bin/python

#pylint: disable=I0011,C0111,C0103

import elftools.elf.elffile
import elftools.elf.segments
import elftools.elf.sections
import elftools.elf.constants
import argparse


def argumentProcessing():
    parse = argparse.ArgumentParser()
    parse.add_argument("-f", "--file", required=True,
                       help="ELF file to parse")
    parse.add_argument("-s", "--sections", action="store_true",
                       help="Show section info")
    parse.add_argument("-e", "--segments", action="store_true",
                       help="Show (loadable) ELF segment info")
    return parse.parse_args()


def banner(string):
    print
    print "___...---===### \033[36;1m%s\033[0m ###===---...___" % string
    print


def generalELFInfo(elffile):
    banner("General ELF Info")
    print "=== Architecture: %s" % elffile.get_machine_arch()
    print "=== Has DWARF Info: %s" % elffile.has_dwarf_info()
    print "=== Number of Sections: %d" % elffile.num_sections()
    print "=== Number of Segments: %d" % elffile.num_segments()
    print "=== Entry EIP: 0x%x" % elffile.header["e_entry"]
    print "=== ELF Header Info:"
    print elffile.header


def segmentInfo(elffile):
    banner("Loadable Segment Info")
    for idx in range(elffile.num_segments()):
        seg = elffile.get_segment(idx)
        if seg.header["p_type"] in ("PT_LOAD", "PT_DYNAMIC"):
            print "VA 0x%x" % seg.header["p_vaddr"],
            print "PA 0x%x" % seg.header["p_paddr"],
            print "OF 0x%x" % seg.header["p_offset"]
            
def sectionInfo(elffile):
    banner("Section Info")
    for idx in range(elffile.num_sections()):
        sec = elffile.get_section(idx)
        print "Section %d: '%s'" % (idx, sec.name),
        print sec.header["sh_type"]

def main():
    opt = argumentProcessing()

    print "Reading ELF file '%s'" % opt.file
    f = file(opt.file)
    ep = elftools.elf.elffile.ELFFile(f)

    generalELFInfo(ep)
    if opt.segments:
        segmentInfo(ep)
    if opt.sections:
        sectionInfo(ep)

if __name__ == "__main__":
    main()
