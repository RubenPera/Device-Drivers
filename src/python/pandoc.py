import typing
import os
import pypandoc

# os.environ.setdefault('PYPANDOC_PANDOC', "'C:\Program Files (x86)\Pandoc\pandoc.exe'")

def main():
    path = "C:\\Users\\Ruben\\Documents\\GitHub\\Device-Drivers\\paper"
    files = []
    pandoc_files = []
    for (dirpath, dirnames, filenames) in os.walk(path):
        
        for file in filenames:
            files.append(format_dirpath_filename(dirpath, file))
        # print(dirpath, filenames):

        # print(dirnames)
        # print(filenames)
    for file in files:
        if file.endswith('md'):
            print(file)
            outputfile = file.replace('md', 'tex', )

            output = pypandoc.convert_file(file, 'tex', outputfile=outputfile)
            print(file)

    # os.system("git")

    

def format_dirpath_filename(dirpath: str, filename: str):
    return "{}\\{}".format(dirpath, filename)

if __name__ == "__main__":
    main()