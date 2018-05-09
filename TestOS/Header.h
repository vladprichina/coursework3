#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <functional>
#include <memory>
#include <locale>
#include <ctime>  
#include "SmartPointers/intrusive_ptr.h"
#include "SmartPointers/ref_counter.h"
using namespace std;

#define typeSLink L".link"		// расширение ссылки
#define typeHLink L".hlink"		// расширение жесткой ссылки(удаляет объект вместе с ссылкой)

#define VRN (+3)				// часовой пояс Воронежа  
#define START_YEAR 1900