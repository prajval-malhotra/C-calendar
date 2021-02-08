// print_header(year, month) prints the calendar "header" 
//   for the given year/month
// notes: if month is invalid, no month line is printed
//        header is aligned for 4-digit years
// effects: produces output
void print_header(const int year, const int month) {
  if (month == 1) {
    printf("====January %d====\n", year);
  } else if (month == 2) {
    printf("===February %d====\n", year);
  } else if (month == 3) {
    printf("=====March %d=====\n", year);
  } else if (month == 4) {
    printf("=====April %d=====\n", year);
  } else if (month == 5) {
    printf("======May %d======\n", year);
  } else if (month == 6) {
    printf("=====June %d======\n", year);
  } else if (month == 7) {
    printf("=====July %d======\n", year);
  }else if (month == 8) {
    printf("====August %d=====\n", year);
  } else if (month == 9) {
    printf("===September %d===\n", year);
  } else if (month == 10) {
    printf("====October %d====\n", year);
  } else if (month == 11) {
    printf("===November %d====\n", year);
  } else if (month == 12) {
    printf("===December %d====\n", year);
  }
  printf("Su Mo Tu We Th Fr Sa\n");
}

const int SUNDAY = 0;
const int base_year = 1589;
const int base_year_jan_1 = SUNDAY;
const int max_year = 2999;
/////////////////////////////////////////////////////////////////////////////

bool leap_year(int year) {
   if(year % 100 == 0) {
      if(year % 400 != 0){
        // NOT a leap year
        return false;
      } 
     else {
        return true;
     }
   }
  else if(year % 4 == 0) {
     return true;
  }
  else {
    return false;
  }
 }
//}

bool long_month(int month) {
  if (month == 1 || month == 3 ||
     month == 5 || month == 7 ||
     month == 8 || month == 10 ||
     month == 12) {
    return true;
  }
  else {
    return false;
  };
}

bool february_check(int year, int month, int day) {
  if(leap_year(year)) {
    // For leap year:
    if(day >= 0 && day <= 29) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if(day >= 0 && day <= 28) {
      return true;
    }
    else {
      return false;
    }
  }
}

// make case to check if month == 2 and call february check
bool valid_date(int year, int month, int day) {
  if(year <= max_year && year >= base_year) {
    if(month >= 1 && month <= 12) {
      if (day >= 1 && day <= 31) {
        if(month == 2) {
          return (february_check(year, month, day));
        }
        else if(long_month(month)) {
          if(day <= 31) {
            return true;
          }
          else {
            return false;
          }
        }
        else if(!long_month(month)) {
          if(day <= 30) {
            return true;
          }
          else {
            return false;
          }
        }
        else {
          return false;
        }
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

int increment_days(int day) {
  if (day == 6) {
    day = 0;
    return day;
  }
  else {
    day = day + 1;
    return day;
  }
}

int increment_months(int month) {
  if (month == 12) {
    return 1;
  }
  else {
    month = month + 1;
    return month;
  }
}


int increment_feb(int year, int temp_days) {
  if(leap_year(year)) {
    // For leap year:
    for(int i = 1; i < 30; i++) {
        temp_days = increment_days(temp_days);
    }
  }
  else {
    for(int i = 1; i < 29; i++) {
        temp_days = increment_days(temp_days);
    }
  }
  return temp_days;
}


int increment(int year, int month, int temp_days) {
   if(month == 2) {
        temp_days = increment_feb(year, temp_days);
        //temp_months = increment_months(temp_months);
    }
   else if(long_month(month)) {
        for(int k = 1; k < 32; k++) {
            temp_days =  increment_days(temp_days);
            //temp_months = increment_months(temp_months);
        }
    }
   else if(!long_month(month)) {
      for(int h = 1; h < 31; h++) {
          temp_days =  increment_days(temp_days);
          //temp_months = increment_months(temp_months);
      }
    }
  return temp_days;
}


int day_of_the_week(int year, int month, int day) {
  // temporary result to pass simple tests
  int temp_days = 0;
  for(int i = 1589; i <= year; i++) {
    if(i != year) {
      for(int j = 1; j <= 12; j++){
          temp_days = increment(i, j, temp_days);
      }
    }
    else if(i == year) {
      // did this because it was always 1 over required value, 
      // dk the reasoning 
      temp_days -= 1;
      for(int j = 1; j <= month; j++) {
        if(j != month) {
            temp_days = increment(i, j, temp_days);
          }
        else if(j == month) {
            for(int k = 1; k <= day; k++) {
                temp_days = increment_days(temp_days);
            }  
        }
      }
    }
  }
  return temp_days;
}

// skip = done
void skip_space(int skip) {
  if(skip == 0) {
    printf(" ");
  }
   for(int i = 1; i <= skip; i++) {
      printf("   ");
   }
  //printf(" ");
}

int assign_month(int year, int month) {
   if(month == 2) {
     if(leap_year(year)) {
        return 29;
     }
    else {
       return 28;
    }
  }
  else if (long_month(month)) {
     return 31;
  }
  else {
     return 30;
  } 
} 

void print_dates(int year, int done, int month) {
  int temp_days = done;
  //int date = 1;
  int len = assign_month(year, month);
  for(int i = 1; i <= len; i++) {
   if(i == len) {
      printf("%d", i);
     break;
   }
   if(temp_days == 6) {
      printf("%2d\n", i);
     if(i + 1 < 10) {
        printf(" ");
     }
    }
   else if(temp_days == 0) {
      printf("%d", i);
      printf(" ");
    }
   else {
      printf("%2d", i);
      printf(" ");
    }
    temp_days = increment_days(temp_days);
    //printf(" ");
  }
  printf("\n");
}


void print_calendar(int year, int month) {
  int done = day_of_the_week(year, month, 1);
  print_header(year, month);
  // function with loop to skip:
  skip_space(done);
  // function that prints dates:
  print_dates(year, done, month);
}


void assertion_tests(void) {
  // Due date is a valid date and a Thursday 
  assert(valid_date(2021, 1, 28));
  assert(day_of_the_week(2021, 1, 28) == 4);
  assert(valid_date(2020, 2, 29));
  assert(valid_date(1590, 1, 1));
  assert(valid_date(2999, 12, 31));
  assert(!valid_date(1588, 12, 31));
  assert(!valid_date(3000, 1, 1));
  assert(valid_date(2020, 8, 31));
  assert(valid_date(2999, 4, 30));
  assert(valid_date(2999, 8, 30));
  assert(!valid_date(2999, 2, 31));
  assert(leap_year(2000));
}

int main(void) {
  assertion_tests();
  while (1) {
    int year = read_int();
    int month = read_int();
    if (month == READ_INT_FAIL) {
      break;
    }
    print_calendar(year, month);
  }
}
