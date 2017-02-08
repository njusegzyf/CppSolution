#include "stdafx.h" // for develop in VS and Windows
#define TEST_FLAG

// #define NDEBUG // for disable debug

// #define INIT_USE_DUMP_DATA // for init data with dump

// #define INIT_USE_FILES_C_STYLE

#define _OUT_  // indicates pram direction
#define _IN_
#define _IN_OUT_

// #define ORDER_CONVERT

// data structures definitions
#include "../headers/DataTypes.h"

#ifndef TEST_FLAG

#include <netinet/in.h>    	// for sockaddr_in
#include <sys/types.h>    	// for socket
#include <sys/socket.h>    	// for socket
#include <stdio.h>       	// for printf
#include <stdlib.h>        	// for exit
#include <unistd.h>
#include <string.h>       	 // for bzero
#include <pthread.h>
#include <sys/errno.h>    	// for errno
#include <netinet/tcp.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>

#include <sys/ioctl.h>
#include <linux/if.h>

#include <time.h>		//for date

#else

#define bzero(a, b)  memset(a, 0, b)

#include <stdio.h>       	// for printf
#include <stdlib.h>        	// for exit
#include <string.h>       	 // for bzero
#include <time.h>		//for date

#endif

#include <vector>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define SERVER_PORT    6666
#define LENGTH_OF_LISTEN_QUEUE  20
#define BUFFER_SIZE 512
#define THREAD_MAX   20

#pragma region Global data 

// char clientaddr[20];

GradeCourses gradeCoursesList[TOTAL_GRADE];

#pragma endregion

#pragma region Help functions

template<typename TComparable>
static bool isRangesOverlap(TComparable range1Begin, TComparable range1End,
  TComparable range2Begin, TComparable range2End)
  {
  assert(range1Begin <= range1End);
  assert(range2Begin <= range2End);

  return (range2Begin <= range1Begin && range2End >= range1Begin)
    || (range2Begin >= range1Begin && range2Begin <= range1End);
  }

#pragma endregion

#pragma region Debug

static inline void printlnDebug(char* msg) {
#ifndef NDEBUG
  printf("Debug Info : %s", msg);
  printf("\n");
#endif
  }

#pragma endregion

static void produceResponse(_IN_ Request* request,
  _OUT_ ResponseHead* response,
  _OUT_ vector<PCourse>* courses)
  {
  assert(request != NULL);
  assert(response != NULL);
  assert(courses != NULL && courses->size() == NULL);

  printlnDebug("Debug Info : In function produceResponse!");

  int resultCount = 0;

  if (QUERYING_BY_COURSENAME == request->type) { // query by course name
    char* queryCourseName = request->data.courseName;

    for (int i = 0; i < TOTAL_GRADE; i++) {
      for (int j = 0; j < gradeCoursesList[i].courseNum; j++) {
        PCourse pCurrentCourse = &gradeCoursesList[i].pAllCources[j];
        if (strstr(pCurrentCourse->name, queryCourseName)) { // find course by name
          resultCount++;
          courses->push_back(pCurrentCourse);
          }
        }
      }

    // mark response state
    if (resultCount != 0) {
      response->state = FIND_COURSE_BY_NAME;
      }
    else {
      response->state = NO_COURSE_BY_NAME;
      }

#ifndef NDEBUG
    printf("Debug Info : Find course by name, num = %d \n", resultCount);
#endif
    }
  else if (QUERYING_BY_GRADE_AND_DATETIME == request->type) { // query grade and datetime
    GradeAndDateTime query = request->data.gradeanddatetime;
    Grade queryGrade = query.grade;
    Weekday queryDate = query.date;
    QueryTime queryTime = query.time;

    // parse query time to a region of time [queryTimeStart, queryTimeEnd]
    char queryTimeBegin;
    char queryTimeEnd;

    switch (queryTime) {
      case AM:
        queryTimeBegin = '0';
        queryTimeEnd = '3';
        break;
      case PM:
        queryTimeBegin = '4';
        queryTimeEnd = '9';
        break;
      case ALLDAY: // all day (by default)
      default:
        queryTimeBegin = '0';
        queryTimeEnd = '9';
        break;
      }

    assert(queryTimeBegin >= '0');
    assert(queryTimeEnd >= queryTimeBegin);
    assert(queryTimeEnd <= '9');

    GradeCourses queryGradeCourses = gradeCoursesList[queryGrade - ONE];
    for (int j = 0; j < queryGradeCourses.courseNum; j++) {
      PCourse pCurrentCourse = &queryGradeCourses.pAllCources[j];
      if (pCurrentCourse->dataTime.date == queryDate // match date
        && isRangesOverlap(pCurrentCourse->dataTime.timeBegin,
          pCurrentCourse->dataTime.timeEnd, queryTimeBegin,
          queryTimeEnd)  //match time
        ) {
        resultCount++;
        courses->push_back(pCurrentCourse);
        }
      }

    // mark response state
    if (resultCount != 0) {
      response->state = FIND_COURSE_BY_DATE;
      }
    else {
      response->state = NO_COURSE_BY_DATE;
      }

#ifndef NDEBUG
    printf("Debug Info : Find course by date, num = %d \n", resultCount);
#endif
    }

  assert(courses->size() == resultCount);

#ifdef ORDER_CONVERT 
  response->InfoSize = htonl(resultCount);
#else
  response->InfoSize = resultCount;
#endif

  response->requestData = request->data;
  }

#ifndef TEST_FLAG

static void *talk_to_client(void *data) {
  //	long long tempSocket = reinterpret_cast<long long>(data);
  //  int new_server_socket = static_cast<int>(tempSocket);

  int new_server_socket = (int)(long)data;

#ifndef NDEBUG
  printf("Debug Info :  In function talk_to_client, new server socket = %d \n", new_server_socket);
#endif

  char buffer[REQUEST_SIZE];
  char sendBuffer[RESPONSE_HEAD_SIZE];
  vector<PCourse> courses;

  while (1) {
    bzero(buffer, REQUEST_SIZE);
    bzero(sendBuffer, RESPONSE_HEAD_SIZE);

    int length = recv(new_server_socket, buffer, REQUEST_SIZE, 0);
    if (length < 0) {
      printf("Server Recieve Data Failed!\n");
      break;
      }
    //receive fin
    if (length == 0) {
      printf("Client exit!\n");
      break;
      }
    if (length != REQUEST_SIZE) {
      printf("Not receive enough data, continue.\n");
      continue;
      }

    assert(REQUEST_SIZE == length);

    produceResponse((Request *)(buffer), (ResponseHead *)sendBuffer,
      &courses);

    printlnDebug("Debug Info : End produce response.");

    // send response head
    send(new_server_socket, sendBuffer, RESPONSE_HEAD_SIZE, 0);

    printlnDebug("Debug Info : Sent response head.");

    // send all course data
    for (unsigned int i = 0; i < courses.size(); i++) {
      send(new_server_socket, courses[i], COURSE_SIZE, 0);
      }
    // Not sure whether the elements in vector is continous
    // send(new_server_socket, courses[0], COURSE_SIZE * courses.size(), 0);

    printlnDebug("Debug Info : Sent response.");

    // clear course data vector
    courses.clear();
    }

  close(new_server_socket);
  pthread_exit(NULL);
  }

#endif

#pragma region Init with files

#ifndef INIT_USE_FILES_C_STYLE

static inline void copyLineString(TChar* dest, const TChar* source, const int length) {
  strncpy(dest, source, length);
  }

static void initAllCourseDataFromFiles(char* basePath) {
  for (int i = 0; i < TOTAL_GRADE; i++) {
    vector<Course> temp;

    string filePath("/Grade");
    filePath.append(1, (char)('1' + i));
    filePath.append(".txt");
    string path = basePath + filePath;

    ifstream fin(path.c_str(), ios::in);

    cout << "Read course file : " << path << endl;

    if (!fin.is_open()) {
      cout << "Cann't read course file : " << path << " , abort!" << endl;
      abort();
      }

    string line;

    while (true) {
      // no more courses
      if (fin.eof()) {
        break;
        }

      // read one course
      Course c;

      if (std::getline(fin, line, '\n') && line.size() != 0) {
        strncpy(c.name, line.c_str(), NAME_BUFFER_BYTE_SIZE);
        }
      else {
        // cout << "Error read grade file.\n";
        break;
        }


      if (std::getline(fin, line, '\n')) {
        strncpy(c.extraInfo, line.c_str(), NAME_BUFFER_BYTE_SIZE);
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (getline(fin, line)) {
        c.grade = (Grade)line.c_str()[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (getline(fin, line)) {
        strncpy(c.classroom, line.c_str(), NAME_BUFFER_BYTE_SIZE);
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (getline(fin, line)) {
        c.dataTime.date = (Weekday)line.c_str()[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (getline(fin, line)) {
        c.dataTime.timeBegin = line.c_str()[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (getline(fin, line)) {
        c.dataTime.timeEnd = line.c_str()[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      temp.push_back(c);

#ifndef NDEBUG
      printf("Debug Info : Get course of name : %s, extra info : %s.\n", c.name, c.extraInfo);
#endif 
      }

    fin.close();

    int size = temp.size();
    PCourse currentGradeCourses = new Course[size];
    for (int j = 0; j < size; j++) {
      currentGradeCourses[j] = temp[j];
      }
    temp.clear();

    gradeCoursesList[i].courseNum = size;
    gradeCoursesList[i].pAllCources = currentGradeCourses;

#ifndef NDEBUG
    printf("Debug Info : Grade %d has %d courses.\n", (i + 1), size);
#endif 
    }
  }

#else

static const int LINE_BUFFER_SIZE = 256;

static void initAllCourseDataFromFiles(char* basePath) {
  for (int i = 0; i < TOTAL_GRADE; i++) {
    vector<Course> temp;

    string filePath("/Grade");
    filePath.append(1, (char)('1' + i));
    filePath.append(".txt");
    string path = basePath + filePath;

    FILE *fp = fopen(path.c_str(), "r");

    cout << "Read course file : " << path << endl;

    if (fp == NULL) {
      cout << "Cann't read course file : " << path << " , abort!" << endl;
      abort();
      }

    char buffer[LINE_BUFFER_SIZE];
    bzero(buffer, LINE_BUFFER_SIZE);

    while (true) {
      // read one course
      Course c;

      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        strncpy(c.name, buffer, 32);
        }
      else {
        // cout << "Error read grade file.\n";
        break;
        }


      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        strncpy(c.extraInfo, buffer, 32);
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        c.grade = (Grade)buffer[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        strncpy(c.classroom, buffer, 32);
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        c.dataTime.date = (Weekday)buffer[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        c.dataTime.timeBegin = buffer[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      if (fgets(buffer, LINE_BUFFER_SIZE, fp) != NULL) {
        c.dataTime.timeEnd = buffer[0];
        }
      else {
        cout << "Error read grade file, abort!\n";
        abort();
        }

      temp.push_back(c);

#ifndef NDEBUG
      printf("Debug Info : Get course of name : %s, extra info : %s.\n", c.name, c.extraInfo);
#endif
      }

    fclose(fp);

    int size = temp.size();
    PCourse currentGradeCourses = new Course[size];
    for (int j = 0; j < size; j++) {
      currentGradeCourses[j] = temp[j];
      }
    temp.clear();

    gradeCoursesList[i].courseNum = size;
    gradeCoursesList[i].pAllCources = currentGradeCourses;

#ifndef NDEBUG
    printf("Debug Info : Grade %d has %d courses.\n", (i + 1), size);
#endif
    }
  }

#endif

#pragma endregion

#pragma region Init with dump course data

static void initAllCourseDataWithDump() {
  for (int i = 0; i < TOTAL_GRADE; i++) {

    PCourse currentGradeCourses = new Course[2];

    strcpy(currentGradeCourses[0].name, "Computer");
    strcpy(currentGradeCourses[0].extraInfo, "(1)");
    currentGradeCourses[0].grade = ONE;
    strcpy(currentGradeCourses[0].classroom, "room1");
    currentGradeCourses[0].dataTime.date = FRI;
    currentGradeCourses[0].dataTime.timeBegin = '5';
    currentGradeCourses[0].dataTime.timeEnd = '6';

    strcpy(currentGradeCourses[1].name, "Computer Network");
    strcpy(currentGradeCourses[1].extraInfo, "(2)");
    currentGradeCourses[1].grade = TWO;
    strcpy(currentGradeCourses[1].classroom, "room2");
    currentGradeCourses[1].dataTime.date = MON;
    currentGradeCourses[1].dataTime.timeBegin = '1';
    currentGradeCourses[1].dataTime.timeEnd = '2';

    gradeCoursesList[i].courseNum = 2;
    gradeCoursesList[i].pAllCources = currentGradeCourses;
    }
  }

#pragma endregion

static void cleanAllCourseData() {
  for (int i = 0; i < TOTAL_GRADE; i++) {
    delete[] gradeCoursesList[i].pAllCources;
    }
  }

#ifndef TEST_FLAG // define server main function

int main(int argc, char **argv) {
  struct sockaddr_in server_addr;

  // init all grades' course data
#ifndef INIT_USE_DUMP_DATA
  if (argc <= 2) {
    initAllCourseDataFromFiles(".");
    }
  else {
    initAllCourseDataFromFiles(argv[1]);
    }
#else
  initAllCourseDataWithDump();
#endif

  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(SERVER_PORT);

  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    printf("Create Socket Failed!\n");
    exit(1);
    }
  const int on = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  if (bind(server_socket, (struct sockaddr*) &server_addr,
    sizeof(server_addr))) {
    printf("Server Bind Port : %d Failed!\n", SERVER_PORT);
    exit(1);
    }

  if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE)) {
    printf("Server Listen Failed!\n");
    exit(1);
    }

  while (1) {
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    int new_server_socket = accept(server_socket,
      (struct sockaddr*) &client_addr, &length);
    if (new_server_socket < 0) {
      printf("Server Accept Failed!\n");
      break;
      }
    // sprintf(clientaddr,"%s",inet_ntoa(client_addr.sin_addr));
    printf("Accepted client: %s : %d\n", inet_ntoa(client_addr.sin_addr),
      ntohs(client_addr.sin_port));

    pthread_t child_thread;
    pthread_attr_t child_thread_attr;
    pthread_attr_init(&child_thread_attr);
    pthread_attr_setdetachstate(&child_thread_attr,
      PTHREAD_CREATE_DETACHED);
    if (pthread_create(&child_thread, &child_thread_attr, talk_to_client,
      (void *)new_server_socket) < 0) {
      printf("pthread_create Failed : %s/n", strerror(errno));
      }

    }

  close(server_socket);

  // clean all resources
  cleanAllCourseData();

  return 0;
  }

#endif

