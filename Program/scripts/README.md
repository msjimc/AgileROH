# Auxiliary scripts

## example_bash_script.sh

```AgileROHFinder``` and ```AgileROHFilterer``` are designed to be used as part of a pipeline, consequently, this script highlights how ```AgileROHFinder``` can be automated. 
Rather that manually enter a series of commands to process each file in a folder of VCF data files, this script iterates through the files, and instructs ```AgileROHFinder``` to save the regions data to a file with the same name as the input file, but with a 'txt' file extension.

The scripts command line structure is:

> bash /script/example_bash_script.sh /program/AgileROHFinder.exe /data/Files/ format

### Where 
* /script/example_bash_script.sh: the name with location of this bash script
* /program/AgileROHFinder.exe:  the name and location of the program to use
* /data/Files/:  the name and location of the folder of the VCF files (the script expects the file extension to be lower case 'vcf')
* format: The format of the regions file (__-a__, __-t__ or __-b__). If you which to process SNPs without an RS id, the __-Y__ option could be combined by adding the __-Y__ option to the format option and putting them all in speech marks i.e. "__-t__ __-Y__". Note space between the __-t__ and the __-Y__.

##  p_FindCommonRegions.py script

Neither program attempt to combine the results of two are more analysis to identify common autozygous regions. This python script will attempt to read all the text files (*.txt) created by ```AgileROHFinder``` or ```AgileROHFilterer``` with the -t format option in a folder and identify the location of the autozygous regions and then create a minimum list of regions present in all the files. Since the analysis files could originate from different data types and different families with a similar phenotype, the script makes no attempt to match the haplotype of common regions. Similarly, it does not exclude regions present in unaffected relatives as they may be autozygous for a different haplotype.  

#### Note
The folder should only contain results files: If other text files are present the script will attempt to read then and probably crash as they will not contain the expected data/format.  

The scripts command line structure is:

> python /script/p_FindCommonRegions.py /data/ResultFiles/

### Where 
* /script/p_FindCommonRegions.py : the name with location of this python script
* /data/ResultFiles/:  the name and location of the folder of the txt files (the script expects the file extension to be lower case 'txt')