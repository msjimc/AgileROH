# AgileROH
Command line application for the detection of autozygous regions from Exome or Affymetrix microarray SNP data.

## Data format
AgileROH can process data formated as VCF file as well as older Affymetrix xls and birdseed files with the required fields/columns described [here](DataFormat.md).

#### Note: 
> AgileROH will only analysis the one patient per file, if a file contains data on multiple individuals only one person will be processed. 


## Creating the programmes

The source code cab be compiled on both Linux and Windows computers as decribed [here](BuildingThePrograms.md).

## Prebuild programs

Both programs have been prebuild for Linux and Windows and placed in the Program folder. Select the appropriate OS version and download the programs.

## Instructions

### ### AgileFROHFinder:
This application requires the name with path of the VCF files, the name with location of the results (text) file and the required results format, for example 

AgileFROHFinder.exe /data/vcf/Patient1.vcf /data/results/Patient1.txt -t

there are three format options:
-t saves the data i a tab delimited file formated as chromosome<tab>Region start<tab>Region end<tab>Regions length
-b saves the regions as a series of coordinates (i.e. chr12:10000000-20000000) that can be entered in to the IGV browser or the Genome browser webpage.
-a creates a file with the regions saves in both formats.

(Note the folder used to save the results file most exist before running the application).

AgileROHFilterer:
This application requires the name with path of the VCF files, the name with location of the filtered vcf file fil, the name with location of the results (text) file, the number of bases added to the start and end of each region to account for error in identifying a regions ends, and the required results format, for example 

AgileROHFilterer.exe /data/vcf/Patient1.vcf /data/filteredvcf/Patient1_filtered.vcf /data/results/Patient1.txt 500000 -t

Regions can be extended by between 0 and 1 Mb.
there are three format options:
-t saves the data i a tab delimited file formated as chromosome<tab>Region start<tab>Region end<tab>Regions length
-b saves the regions as a series of coordinates (i.e. chr12:10000000-20000000) that can be entered in to the IGV browser or the Genome browser webpage.
-a creates a file with the regions saves in both formats.

(Note the folder used to save the results file most exist before running the application).

A webpage version of this page can be found here: https://www.dna-leeds.co.uk/agile/AgileROH/
