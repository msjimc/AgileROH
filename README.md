# AgileROH
Command line application for the detection of autozygous regions from Exome or Affymetrix microarray SNP data.

## Data format
AgileROH can process data formated as VCF file as well as older Affymetrix xls and birdseed files with the required fields/columns described [here](DataFormat.md).

#### Note: 
> AgileROH will only analysis the one patient per file, if a file contains data on multiple individuals only one person will be processed. 


## Creating the programs

The source code cab be compiled on both Linux and Windows computers as described [here](BuildingThePrograms.md).

## Prebuild programs

Both programs have been prebuild for Linux and Windows and placed in the Program folder. Select the appropriate OS version and download the programs ([Linux](Program/Linux) or [Windows](Program/LiWindowsnux)). Due to security policies of some organisations, downloading programs on a Windows computer may not be straight forward, but this guide may help  

## Running the programs

Both programs require very similar commands, with ```AgileROHFilterer``` requiring the name of the file to save the filtered variants too. Both programs export the autozygous regions to a text file  

### AgileFROHFinder:
This application requires the name with path of the input data file (microArray SNP genotype file or the VCF file), the name with location of the results (text) file and the required results format, for example: 

> AgileFROHFinder.exe /data/vcf/Patient1.vcf /data/results/Patient1.txt -t

or

> AgileFROHFinder.exe /data/vcf/Patient1.vcf /data/results/Patient1.txt -t -Y

there are three format options (see table below):  
__-t__ Saves the data i a tab delimited file formated as chromosome<tab>Region start<tab>Region end<tab>Regions length  
__-b__ Saves the regions as a series of coordinates (i.e. chr12:10000000-20000000) that can be entered in to the IGV browser or the Genome browser webpage.  
__-a__ Creates a file with the regions saves in both formats.  
 

The last parameter is optional and if set to __-Y__ (or __-y__), the program will process all variants with or without a RS ID. If the value is __-N__ (or __-n__) or absent only variants with an RS ID will be processed. 

(Note the folder used to save the results file most exist before running the application).

### AgileROHFilterer:
This application requires the name with path of the VCF files, the name with location of the filtered vcf file fil, the name with location of the results (text) file, the number of bases added to the start and end of each region to account for error in identifying a regions ends, and the required results format, for example 

> AgileROHFilterer.exe /data/vcf/Patient1.vcf /data/filteredvcf/Patient1_filtered.vcf /data/results/Patient1.txt 500000 -t

or  

> AgileROHFilterer.exe /data/vcf/Patient1.vcf /data/filteredvcf/Patient1_filtered.vcf /data/results/Patient1.txt 500000 -t -Y

Regions can be extended by between 0 and 1 Mb.
there are three format options:  
__-t__ saves the data i a tab delimited file formated as chromosome<tab>Region start<tab>Region end<tab>Regions length  
__-b__ saves the regions as a series of coordinates (i.e. chr12:10000000-20000000) that can be entered in to the IGV browser or the Genome browser webpage.  
__-a__ creates a file with the regions saves in both formats.  
__-Y__  

(Note the folder used to save the results file most exist before running the application).

A webpage version of this page can be found here: https://www.dna-leeds.co.uk/agile/AgileROH/
