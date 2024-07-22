# Project title
Qt Kviz: Interactive Quiz Application with Database Integration

## Description
Qt Kviz is an interactive quiz application designed to challenge users with three quiz themes. Upon launching the application, users are prompted to enter their name and select one of the available quizzes. Each quiz contains multiple questions that users navigate through, with options to skip questions or review previous answers.

At the conclusion of each quiz, users receive immediate feedback on their performance, including the number of correct answers. A detailed summary table displays all questions, indicating which answers were correct or incorrect. Additionally, users have the option to view highscores, showing the top three performers from all quiz categories.

Qt Kviz includes a custom-built database to load and manage quiz content, ensuring a dynamic and engaging experience for quiz enthusiasts. The application is designed for ease of use, allowing users to exit using the standard window controls.

Challenge yourself with Qt Kviz today!

## Installation
### Prerequisites
- Qt 6.6.3
- Qt Creator (download and install from https://www.qt.io/download) - Open Source version is used here (Qt Creator 13.0.2 - based on Qt 6.6.3 (GCC 10.3.1 20210422 (Red Hat 10.3.1-1), x86_64))

### Installation Steps
1. Clone the repository from GitHub:
git clone https://github.com/sMirkovicc/qt_kviz
2. Open Qt Creator.
3. Click on "File" > "Open File or Project".
4. Navigate to the directory where you cloned the repository and open the `.pro` file.
5. Adjust database path.
6. Build and run the project using the green play button or `Ctrl + R`.

### Additional Notes - Step 5. Adjusting the database path
1. Open 'main.cpp' in Qt Creator:

Navigate to the 'main.cpp' file of your project in Qt Creator.

2. Locate the 'DbManager' initialization:

In 'main.cpp', find the line where the 'DbManager' object ('db') is initialized. It should look similar to this:

DbManager db("/home/Sara/saraqt/qt_kviz/database/kviz.db");

3.Edit the database path:

Replace the path "/home/Sara/saraqt/qt_kviz/database/kviz.db" with the absolute path to the database file ('kviz.db') that you downloaded from the repository.
Make sure to use forward slashes ('/') for directory separators, even on Windows.

Example (on Linux or macOS):
DbManager db("/absolute/path/to/your/downloaded/database/kviz.db");

Example (on Windows):
DbManager db("C:/Users/YourUsername/Documents/qt_kviz/database/kviz.db");

4. Save the changes:

Save the 'main.cpp' file after editing the database path.

Notes:
Ensure that the path you provide matches the actual location of the 'kviz.db file' on your computer.
Users should replace "..." with the appropriate absolute path on their system where they have downloaded the database file.
