#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <functional>
#include <memory>
#include <locale>
#include <codecvt>
#include "intrusive_ptr.h"
#include "ref_counter.h"

using namespace std;

//#define DECLARE_SMART(class_name, spname) class class_name;\
//	typedef std::shared_ptr<class_name> spname;