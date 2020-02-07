#ifndef HEADER
#define HEADER

#include <QDebug>
#include <QMessageBox>
#include <QSound>
#include <QLineEdit>
#include <QRegExp>
#include <QFile>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>

#include <fstream>
#include <ostream>
#include <istream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include <time.h>

using namespace std;

#include <assert.h>
#include <typeinfo>

#define kLn "\r\n"

template <class T>
using cr = const T&;

#define AssertEqual(a, b) \
if ( (a) != (b) ) \
{ \
    qDebug() << "AssertEqual failed" << a << "~" << b <<__LINE__ << __FILE__; \
    terminate(); \
}

#define AssertNotEqual(a, b) \
if ( (a) == (b) ) \
{ \
    qDebug() << "AssertNotEqual failed" << a << "~" << b <<__LINE__ << __FILE__; \
    terminate(); \
}

#endif // HEADER
