import sys
from file_handler import FileHandler

if __name__ == "__main__":
    file_name = sys.argv[1]
    file_handler = FileHandler(f"data/OR-Library/{file_name}.txt")
    
    A, c = file_handler.process()
    print(A)
    
    file_handler.write_file(f"data/OR-Library-Custom/{file_name}.txt")
