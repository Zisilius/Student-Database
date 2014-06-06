#include <iostream>
#include <fstream>
#include <map>
#define TABLE_SIZE 4

typedef  std::map<std::string, std::map<std::string, std::string>> smap;

int splitLine(const std::string&, const char&, std::string[]);
int output_db(std::ostream& os, smap& m);
int mkdb(const std::string&, smap&);

template <typename T>
bool mapLine(const std::string& s, T& m)
{
  std::string arr[TABLE_SIZE];
  if (splitLine(s, ':', arr) != TABLE_SIZE)
    return false;
  m[arr[0]]["email"] = arr[1];
  m[arr[0]]["title"] = arr[2];
  m[arr[0]]["date"] = arr[3];
  return true;
}

int main()
{
  smap table;

  if (mkdb("student.db", table)) {
    std::cerr << "Error: problem with assembling the database" << std::endl;
    return 1;
  }

  if (output_db(std::cout, table)) {
    std::cerr << "Error: can't output the database" << std::endl;
    return 1;
  }

  return 0;
}

int mkdb(const std::string& fileName, smap& m)
{
  std::fstream file(fileName);

  if (!file) {
    return 1;
  }

  std::string temp;
  while (!file.eof()) {
    std::getline(file, temp);
    if (temp.size() == 0)
      continue;
    if (!mapLine(temp, m))
      return 1;
  }

  file.close();
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

  return index;
}

int output_db(std::ostream& os, smap& m)
{
  if (m.empty())
    return 1;

  for (smap::iterator iter = m.begin(); iter != m.end(); iter++) {
    os << iter->first << ":" << std::endl;
    for (std::map<std::string, std::string>::iterator j= m[iter->first].begin();
         j != m[iter->first].end(); j++) 
      os << "\t" << j->first << " -> " << j->second << std::endl;
  }
  return 0;
}
