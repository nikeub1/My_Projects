    # File Organizer
    #### Video Demo:  [My project](https://youtu.be/XadJWA7Qfjo)
    #### Description:
    ### What is the aim of the project?
    The aim of the project is to allow the user to organize their files, in a selected directory, based on the extension. It is not wrong to ask why not just organize them in a MIME type manner, the reason is that there are some extentions that are not correctly classified by their respective extentions. Therefore, it's much easier to just divide the directory into smaller pieces based on file extention types instead of havinng to manually assign each extention to their category.

    
    ** Challenges ** 
    This took a bit more than two weeks due to the challenge in finding the correct functions from the modules documentation and debugging the code. The most difficult part was the test file, a lot of time was spent on [geekstogeeks](https://www.geeksforgeeks.org/python-testing/).
    One of the most challenging function to implement was ** get_input **.
    At first attempt to apply this function, a recurrsion error was encountered. I had get_input and on_submit as seperate functions, thus the get_input would recursively call itself in a infinite loop. After countless debugging sessions the solution was to create a nested function which seemed to work... "If it works dont touch it"!

    ### libraries
    ** Tkinter **:
    This module allows the user to create basic UI and assign functionality.
    Here is the link to the tkinter documentation [Tkinter](https://docs.python.org/3/library/tk.htm).
    Here is the command to install the tkinter module `pip install tk`

    ** os **
    This module allows the user to manipulate individual file or directory paths. Open, read or write files, Which was very useful in this project.
    Here is the link to the os documentation [os](https://docs.python.org/3/library/os.html).

    ** Shutill **
    This module offers a number of high-level operations on files and collections of files. In particular, functions are provided which support file copying and removal.
    As seen in the auto_organize and organize_type functions.

    ### organize.py

    ## select_directory
    This function allows the user to select the directory they wish to organize. After the user selects the directory, they are meeted with a list of the files' names, their respective extentions and size. This might seem pointless but it's useful for the user to decide wether they want the directory to be organized by a specific file extentiont or completely organize it. At the bottom two buttons are displayed **Organize by Extension Type** and **Auto organize**.

    ## organize_type
    The function organizes the files within the chosen directory by their extention, creating folders/directories that are named the extention of the files that will be moved there.

    ## make_dir
    This function has two arguments, the name for the directory * extension * and the selected directory * selected_dir *. As the name implies, the function creates a directory within the selected directory.

    ## list_files
    The function is straight forward, it passes the lists of files in the selected directory to the ** print_content ** function. Which then displays the files for the user to view and decide how they wish to oranize them.

    ## print_content
    This function accepts * files * as an argument, it displays the files in a table format with headers "file name", "file extension" and "file size".

    ## convert_size
    Accepts an argument *size_bytes*, since the file size is returned in bytes it's more comprehensible to convert them in appropriate units(bytes, Kb, MB, GB) and return it.
