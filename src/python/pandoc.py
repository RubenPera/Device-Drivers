import typing
import os
import pypandoc

def main():
    path = "C:\\Users\\Ruben\\Documents\\GitHub\\Device-Drivers\\paper\\md"
    files = []

    for (dirpath, dirnames, filenames) in os.walk(path):
        for file in filenames:
            files.append(format_dirpath_filename(dirpath, file))

    # files = filter_files(files, 'sub')

    write_files(files)

def filter_files(files, f):
    return [file for file in files if f in file]

def write_files(files):
    for file in files:
        if file.endswith('md'):
            outputfile = file.replace('md', 'tex', ).replace(' ', '_')

            try:
                with open(outputfile, 'x') as f:
                    pass
            except:
                pass
            print(file)
            
            pypandoc.convert_file(file, 'tex', format='gfm', outputfile=outputfile, extra_args=['--top-level-division=chapter'])


def format_dirpath_filename(dirpath: str, filename: str):
    return "{}\\{}".format(dirpath, filename)


if __name__ == "__main__":
    main()
