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

#define typeSLink L".link"		// ���������� ������
#define typeHLink L".hlink"		// ���������� ������� ������(������� ������ ������ � �������)

#define VRN (+3)				// ������� ���� ��������  
#define START_YEAR 1900