import os
import shutil
import tkinter as tk
from tkinter import filedialog, ttk, messagebox


def main():
    global root, file_frame, directory_frame, button_frame
    root = tk.Tk()
    root.title("Main Window")
    root.geometry("500x500")
    label = tk.Label(root, text="File Organizer")
    label.pack(pady=10)

    button = tk.Button(root, text="Select a Directory", command=select_directory)
    button.pack(pady=10)
    
    directory_frame = tk.Frame(root)
    directory_frame.pack(pady=5)
    
    file_frame = tk.Frame(root)
    file_frame.pack(fill="both", expand=True, pady = 5)

    button_frame = tk.Frame(root)
    button_frame.pack(pady=5)
    
    
    root.mainloop()

def select_directory():
    script_dir = os.path.dirname(__file__)
    
    global selected_dir
    
    selected_dir = filedialog.askdirectory(title="Select folder:", initialdir=script_dir)
    print(f"Directory: {selected_dir} was selected")
    
    list_files()
    
    for widget in directory_frame.winfo_children():
        widget.destroy()
        
    for widget in button_frame.winfo_children():
        widget.destroy()
    
    
    label = tk.Label(directory_frame,text = f"Directory selected: {selected_dir}", bg="white")
    label.pack()
    
    button1 = tk.Button(button_frame, text="Organize by Extension Type", command=lambda:organize_type(selected_dir))
    button1.pack(side=tk.LEFT,padx=5,pady=5)
    
    button2 = tk.Button(button_frame, text="Auto organize", command=lambda:auto_organize(selected_dir))
    button2.pack(side=tk.LEFT, padx=5,pady=5)
    
    button_frame.pack_configure(anchor="center")
    
    
def organize_type(selected_dir, extension=None):
    if extension == None:
        extension = get_input()
    
    file_paths = [os.path.join(selected_dir,f) for f in os.listdir(selected_dir) if extension in os.path.basename(f) and os.path.isfile(os.path.join(selected_dir,f))]
    
    dir = os.path.join(selected_dir, extension)
        
    make_dir(extension,selected_dir)
    
    for file in file_paths:
        if os.path.exists(file):
            shutil.move(file, os.path.join(dir,os.path.basename(file)))
            print(f"{file} moved to {dir}")
        else:
            print("File not found")
    
    messagebox.showinfo("Information", "The organization has finished.")
    
def get_input():
    global new_root, entry
    
    new_root = tk.Tk()
    new_root.title("Extension Selection")
    new_root.geometry("300x150")
    
  
    text = tk.Label(new_root, text="Enter the extension (without dot) to select:")
    text.pack(pady=5)
    
    entry = tk.Entry(new_root)
    entry.pack(pady=5)

    def on_submit():
        global ext
        ext = entry.get()  
        new_root.destroy()  

    button = tk.Button(new_root, text="Submit", command=on_submit)
    button.pack()
    
    new_root.mainloop()
    
    return ext

def auto_organize(selected_dir):
    file_paths = [os.path.join(selected_dir,f) for f in os.listdir(selected_dir) if os.path.isfile(os.path.join(selected_dir,f))]
    files = [f for f in os.listdir(selected_dir) if os.path.isfile(os.path.join(selected_dir,f))]
    ext = set()
    for e in files:
        n,e = os.path.splitext(e)
        e = e.strip(".")
        ext.add(e)
        make_dir(e,selected_dir)
    
    for file in file_paths:
        if os.path.exists(file):
            name, e = os.path.splitext(os.path.basename(file))
            e = e.strip(".")
            if e in ext:
                dest_dir = os.path.join(selected_dir, e)
                
                shutil.move(file, os.path.join(dest_dir, os.path.basename(file)))
                print(f"{file} moved to {dest_dir}")
        else:
            print("File not found")
            
    messagebox.showinfo("Information", "The organization has finished.")
    

def make_dir(extension, selected_dir):
    dir = os.path.join(selected_dir,extension)
    if not os.path.exists(dir):
        print(f"{extension} was created in directory {selected_dir}]")
        os.makedirs(dir)
    else:
        print(f"{extension} directory exists in {dir}")

def list_files():
    files = [f for f in os.listdir(selected_dir) if os.path.isfile(os.path.join(selected_dir,f))]
    print_content(files)

def print_content(files):
    columns = ["File Name", "File Extension", "File Size"]
    for widget in file_frame.winfo_children():
        widget.destroy()
    tree = ttk.Treeview(file_frame,columns=columns, show="headings")
            
    for col in columns:
        tree.heading(col, text=col)
        tree.column(col, anchor="center")
        
    for item in files:
        f, ext = os.path.splitext(item)
        item = os.path.join(selected_dir,item)
        f_size = convert_size(os.path.getsize(item))
        tree.insert("","end",values=(f,ext,f_size))
        
    scrollbar_v = ttk.Scrollbar(file_frame, orient=tk.VERTICAL, command=tree.yview)
    tree.configure(yscroll=scrollbar_v.set)
    scrollbar_v.pack(side=tk.RIGHT, fill=tk.Y)
    
    scrollbar_h = ttk.Scrollbar(file_frame, orient=tk.HORIZONTAL, command=tree.xview)
    tree.configure(xscrollcommand=scrollbar_h.set)
    scrollbar_h.pack(side=tk.BOTTOM, fill=tk.X)
    
    tree.pack(fill=tk.BOTH, expand=True)
    
def convert_size(size_bytes):
    units = ["bytes", "KB", "MB", "GB", "TB"]
    unit_index = 0
    while size_bytes >= 1024 and unit_index < len(units) - 1:
        size_bytes /= 1024
        unit_index += 1
    return f"{size_bytes:.2f} {units[unit_index]}"
    
if __name__ == "__main__":
    main()