#include "../stdafx.h" // for develop in VS

#ifndef DATAGRAM_H_
#define DATAGRAM_H_

#pragma pack(push, 1) // same as #pragma pack(push) + #pragma pack(1)
// #pragma pack(push)  //保存对齐状态
// #pragma pack(1)     //设定为1字节对齐

// #define USING_WCHAR

#ifdef USING_WCHAR
typedef wchar_t TChar;
#else
typedef char TChar;
#endif

enum Type:char{
    QUERYING_BY_COURSENAME='1',
    QUERYING_BY_GRADE_AND_DATETIME
    };

enum ResponseState:char{
    FIND_COURSE_BY_NAME='A',
    NO_COURSE_BY_NAME,
    FIND_COURSE_BY_DATE = '1',
    NO_COURSE_BY_DATE 
    };

enum Weekday:char{MON='1',TUE,WED,THU,FRI};

enum Grade:char{ONE='1',TWO,THREE,FOUR};

enum QueryTime:char{ALLDAY='0',AM,PM};

static const int TOTAL_GRADE = 4;

typedef struct _GradeAndDateTime{
    Grade grade;      //1,2,3,4
    Weekday date;     //1,2,3,4,5
    QueryTime time;   //0:ALLDAY 1:AM (maps to time '0' - '3') 2:PM (maps to time '4' - '9')
    } GradeAndDateTime;

static const int NAME_BUFFER_LENGTH = 32;

#ifdef USING_WCHAR
static const int NAME_BUFFER_BYTE_SIZE = NAME_BUFFER_LENGTH * 2;
#else
static const int NAME_BUFFER_BYTE_SIZE = NAME_BUFFER_LENGTH;
#endif

typedef union _RequestData{
    TChar courseName[NAME_BUFFER_BYTE_SIZE];	// course name
    GradeAndDateTime gradeanddatetime;
    } RequestData;

// Request send from client to server 
typedef struct _Request{
    char type; // 1 means Querying By Course Name, 2 means Querying By Grade and DateTime
    RequestData data;
    } Request;

static const int REQUEST_SIZE = sizeof(Request);

typedef struct _CourseDateTime {
    Weekday date;
    char timeBegin; // '0' - '9'
    char timeEnd; 
    } CourseDateTime;

typedef struct _Course{
    TChar name[NAME_BUFFER_BYTE_SIZE];
    TChar extraInfo[NAME_BUFFER_BYTE_SIZE];
    Grade grade;
    TChar classroom[NAME_BUFFER_BYTE_SIZE];
    CourseDateTime dataTime;
    } Course;

static const int COURSE_SIZE = sizeof(Course);

typedef Course* PCourse;

typedef struct _GradeCourses {
    int courseNum;
    PCourse pAllCources;
    } GradeCourses;

// Respond head send from server to client
typedef struct _ResponseHead{
    ResponseState state; // A:find course by name, B:no course by name, '1': find course in datetime, '2'no course in datetime
    int InfoSize;	       // courses count
    RequestData requestData;
    } ResponseHead;

static const int RESPONSE_HEAD_SIZE = sizeof(ResponseHead);

#pragma pack(pop) // 恢复对齐状态

#endif /* DATAGRAM_H_ */
