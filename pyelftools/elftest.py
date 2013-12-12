#!/usr/bin/python

"""
Toy example for using PyELFTools by Eli Benderski.
"""

#pylint: disable=I0011,C0111,C0103

import elftools.elf.elffile
import elftools.elf.segments
import elftools.elf.sections
import elftools.elf.constants
import argparse
import subprocess


def argumentProcessing():
    """
    Command line argument processing
    """
    parse = argparse.ArgumentParser()
    parse.add_argument("-f", "--file", required=True,
                       help="ELF file to parse")
    parse.add_argument("-s", "--sections", action="store_true",
                       help="Show section info")
    parse.add_argument("-e", "--segments", action="store_true",
                       help="Show (loadable) ELF segment info")
    parse.add_argument("-y", "--symbols", action="store_true",
                       help="Show symbols")
    parse.add_argument("-C", "--demangle", action="store_true",
                       help="Demangle C++ symbol names")
    return parse.parse_args()


def banner(string):
    """Print string as a fancy banner."""
    print
    print "___...---===### \033[36;1m%s\033[0m ###===---...___" % string
    print


def generalELFInfo(elffile):
    """
    Display general header information from the ELF file
    """
    banner("General ELF Info")
    print "=== Architecture: %s" % elffile.get_machine_arch()
    print "=== Has DWARF Info: %s" % elffile.has_dwarf_info()
    print "=== Number of Sections: %d" % elffile.num_sections()
    print "=== Number of Segments: %d" % elffile.num_segments()
    print "=== Entry EIP: 0x%x" % elffile.header["e_entry"]
    print "=== ELF Header Info:"
    print elffile.header


def segmentInfo(elffile):
    """
    Display information about the ELF file's loadable segments.
    """
    banner("Loadable Segment Info")
    for idx in range(elffile.num_segments()):
        seg = elffile.get_segment(idx)
        if seg.header["p_type"] in ("PT_LOAD"):
            print "VA 0x%x" % seg.header["p_vaddr"],
            print "PA 0x%x" % seg.header["p_paddr"],
            print "OF 0x%x" % seg.header["p_offset"]

def sectionInfo(elffile):
    """
    Display the ELF file's section names and types.
    """
    banner("Section Info")
    for idx in range(elffile.num_sections()):
        sec = elffile.get_section(idx)
        print "Section %d: '%s'" % (idx, sec.name),
        print sec.header["sh_type"]

def singleSymbolInfo(sym, demangle):
    """
    Print information about a single symbo if it is a function
    or variable
    """
    st_type = sym.entry["st_info"]["type"]
    if st_type in ("STT_FUNC", "STT_OBJECT", "STT_TLS"):
        if demangle:
            name = subprocess.check_output(["c++filt", sym.name]).strip()
        else:
            name = sym.name
        print "\033[33m0x%08x\033[0m %15s \033[32m%s\033[0m"  % \
            (sym.entry["st_value"], st_type, name)


def symbolInfo(elffile, demangle):
    """
    Show symbols in ELF file
    """
    banner("Symbol Info")
    for idx in range(elffile.num_sections()):
        sec = elffile.get_section(idx)
        # pyelftools creates a SymbolTableSection for SHT_SYMTAB and
        # SHT_DYNSYM sections
        if isinstance(sec, elftools.elf.sections.SymbolTableSection):
            print "Found a symbol table in section %d (%s)" % (idx, sec.name)
            for sym in sec.iter_symbols():
                singleSymbolInfo(sym, demangle)

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
    if opt.symbols:
        symbolInfo(ep, opt.demangle)

if __name__ == "__main__":
    main()
