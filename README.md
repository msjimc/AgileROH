# AgileROH
Command line application for the detection of autozygous regions from Exome or microarray SNP data

The code can be used to build two applications:
AgileROHFinder:- which identifies autozygous regions in either next generation sequencing variant data in (uncompressed) vcf files or microarray SNP genotype data,
AgileROHFilterer:- which identifies autozygous regions and then creates a 2nd VCF that contins variants in the autozygous regions.

The code can be compiled on either a Windows computer using Visual Studio or a Linux computer using the g++ compiler.

Linux
Place all the files in an empty folder and enter the folder and issue one or bother of the commands below:

g++ -g 	AffyEngine.cpp 	CompareRegionList.cpp 	AgileROHFinder.cpp 	GetRegions.cpp 	methods.cpp 	parameters.cpp 	Region.cpp 	SNP.cpp -o 	AgileROHFinder.exe 2> 	AgileROHFinder_error.txt
g++ -g 	AffyEngine.cpp 	CompareRegionList.cpp 	AgileROHFilter.cpp 	GetRegions.cpp 	methods.cpp 	parameters.cpp 	Region.cpp 	SNP.cpp 	VCFFilter.cpp -o 	AgileROHFilter.exe 2> 	AgileROHFilter_error.txt

This should build the selected application with any errors or warnings stored in the appropriate error file.

Windows - Visual Studio
Create an empty C++ windows console application and select the required source code (*.cpp) and header (*.h) files. 

AgileROHFinder: 

AffyEngine.cpp, CompareRegionList.cpp, AgileROHFinder.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp, and AffyEngine.h, CompareRegionList.h, GetRegions.h, methods.cpp, parameters.h, Region.h, SNP.h, dirent.h.

AgileROHFilter: AffyEngine.cpp, CompareRegionList.cpp, AgileROHFilter.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp, VCFFilter.cpp and AffyEngine.h, CompareRegionList.h, GetRegions.h, methods.h, parameters.h, Region.h, SNP.h, VCFFilter.h, dirent.h.

Unlike on Linux systems the dirent.h header files is typically included in the installation, consequently you need to tell Visual Studio to look for a local copy of the dirent.h file. This is done by changing all occurences of:

#include <dirent.h> 

to

#include "dirent.h"

and adding 

#include "dirent.h"

to "AgileROHFinder.cpp" and/or "AgileROHFilter.cpp"

The create the applications by selecting the Build > Batch Build menu option. 

Usage:
Usage is the same whether used on a Windows or Linux server/computer.

AgileFROHFinder:
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
