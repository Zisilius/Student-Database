#include <iostream>
#include <fstream>
#include <map>

typedef  std::map<std::string, std::map<std::string, std::string>> smap;

int splitLine(const std::string&, const char&, std::string[]);
bool mapLine(const std::string& s, smap& m);
void outputDb(std::ostream& os, smap& m);

int main()
{
  std::fstream file("student.db");

  if (!file) {
    std::cerr << "The file is fucked" << std::endl;
    return 1;
  }

  smap table;
  std::string temp;
  while (!file.eof()) {
    std::getline(file, temp);
    if (temp.size() == 0)
      continue;
//    std::cout << temp << std::endl;
    if (mapLine(temp, table)) {
      std::cerr << "There is a problem with mapLine" << std::endl;
      return 1;
    }
  }

  file.close();

//  std::cout << table["Kevin Morris"]["email"] << std::endl;
  outputDb(std::cout, table);

  return 0;
}

int splitLine(const std::string& s, const char& c, std::string arr[]) 
{
  size_t pos = 0, old = 0, index = 0;

  while ((pos = s.find(c, old)) != std::string::npos) {
    arr[index++] = s.substr(old, pos - old);
    old = pos + 1;
  }
  arr[index++] = s.substr(old, s.size() - old);

  return index ;
}

bool mapLine(const std::string& s, smap& m)
{
  std::string arr[4];
  if (splitLine(s, ':', arr) != 4)
    return false;
  m[arr[0]]["email"] = arr[1];
  m[arr[0]]["comment"] = arr[2];
  m[arr[0]]["date"] = arr[3];
  return true;
}

void outputDb(std::ostream& os, smap& m)
{
  for (smap::iterator iter = m.begin(); iter != m.end(); iter++) {
    os << iter->first << ":" << std::endl;
    for (std::map<std::string, std::string>::iterator j= m[iter->first].begin();
         j != m[iter->first].end(); j++) 
      os << "\t" << j->first << " -> " << j->second << std::endl;
  }
}
