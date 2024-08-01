# Project title
Qt Kviz: Interactive Quiz Application with Database Integration

## Description
Qt Kviz is an interactive quiz application designed to challenge users with different quiz themes. Upon launching the application, users are prompted to enter their name and select one of the available quizzes. Each quiz contains multiple questions that users navigate through, with options to skip questions or review previous answers.

At the conclusion of each quiz, users receive immediate feedback on their performance, including the number of correct answers. A detailed summary table displays all questions, indicating which answers were correct or incorrect. Additionally, users have the option to view highscores, showing the top three performers from all quiz categories. Quiz can be played multiple times without exiting the application.

Qt Kviz includes a custom-built database to load and manage quiz content, ensuring a dynamic and engaging experience for quiz enthusiasts. The application is designed for ease of use, allowing users to exit using the standard window controls.

Challenge yourself with Qt Kviz today!

## Installation
### Qt6 dependencies
- Open terminal and run the commands:
sudo apt-get update
sudo apt-get install build-essential qt6-base-dev

### Installation Steps
1. Clone the repository from GitHub:
git clone https://github.com/sMirkovicc/qt_kviz.git

2. Open the cloned repository:
cd qt_kviz

3. Adjust the database path (See Additional Notes)

4. Create a build directory and navigate into it:
mkdir build
cd build

5. Generate the Makefile with qmake:
qmake ../qt_kviz.pro

6. Build the project:
make

7. Run the executable:
./qt_kviz

### Additional Notes - Step 3. Adjusting the database path
1. Make sure you are currently in the qt_kviz directory

2. Move the ".qt_kviz" file to your home directory:
mv .qt_kviz ~/ 

3. Verify that the file is in your home directory (Look for .qt_kviz in the output list):
ls -a ~
