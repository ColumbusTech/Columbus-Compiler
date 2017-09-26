#include <Interpreter.hpp>

namespace ColumbusCompiler
{

  C_Interpreter::C_Interpreter(int argc, char** argv)
  {
    if (argc != 3)
      return;

    mSrcFile = argv[1];
    mDstFile = argv[2];

    mInited = true;
  }

  bool C_Interpreter::load()
  {
    std::ifstream file;
    file.open(mSrcFile);

    if (!file.is_open())
    {
      file.close();
      return false;
    }

    std::string string;

    int i = 0;

    while(getline(file, string))
    {
      i++;
      std::stringstream ss(string);

      std::string line;

      while(ss >> line)
      {
        if (mTypes.size() > 0)
        {
          if (mTypes.back().type == 0)
          {
            if (line[0] == ':')
            {
              mTypes.back().endOperator = true;
              mTypes.back().afterType = false;
              mTypes.back().afterTypeI = 0;
            } else if(isStringNumber(line) || isStringNumber(line.substr(0, line.size() - 1)))
            {
              mTypes.back().afterType = true;
              mTypes.back().afterTypeI = atoi(line.c_str());

              if (line[line.size() - 1] == ':')
                mTypes.back().endOperator = true;

              continue;
            }
          }

          if (mTypes.back().type == 1)
          {
            if (line[0] == '.')
              mTypes.back().endOperator = true;
          }

          if (mTypes.back().type == 2)
          {
            if (mTypes.back().afterType == false)
            {
              mTypes.back().afterType = true;

              if (line[line.size() - 1] == ';')
              {
                mTypes.back().endOperator = true;
                mTypes.back().afterTypeS = line.substr(0, line.size() - 1);
              } else
              {
                mTypes.back().afterTypeS = line;
              }

              mTypes.back().line += ' ' + mTypes.back().afterTypeS;

              continue;
            }
          }
        }

        C_Type type;
        type.type = getType(line);
        type.str = i;
        type.line = line;
        type.endOperator = getEndOperator(type.type, line);

        mTypes.push_back(type);
      }
    }

    file.close();

    return true;
  }

  bool C_Interpreter::getErrors()
  {

    bool ret = true;

    for (size_t i = 0; i < mTypes.size(); i++)
    {
      if (mTypes[i].type == -1)
      {
        C_Error("%s: %i: Unknown type `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
        ret = false;
      }

      if (mTypes[i].endOperator == false)
      {
        switch (mTypes[i].type)
        {
          case 0:
            C_Error("%s: %i: expected ':' `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
          case 1:
            C_Error("%s: %i: expected '.' `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
          default:
            C_Error("%s: %i: expected ';' `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
        }
        ret = false;
      }
    }

    return ret;
  }

  void C_Interpreter::save()
  {
    std::ofstream file;
    file.open(mDstFile);

    if (!file.is_open())
    {
      file.close();
      return;
    }

    for (size_t i = 0; i < mTypes.size(); i++)
    {
      switch (mTypes[i].type)
      {
        case 0:
        {
          if (mTypes[i].afterType == false)
            file << "org 0" << std::endl;

          if (mTypes[i].afterType == true)
            file << "org " << mTypes[i].afterTypeI << std::endl;

          break;
        };

        case 1:
        {
          file << "end." << std::endl;
          break;
        };

        case 2:
        {
          break;
        };
      }
    }

    file.close();
  }

  void C_Interpreter::compile()
  {
    if (load() == false)
      return;

    if (getErrors() == false)
      return;

    save();
  }

  bool C_Interpreter::isStringNumber(std::string str)
  {
    return !str.empty() && std::find_if(str.begin(),
        str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
  }

  int C_Interpreter::getType(std::string str)
  {
    if (str.compare(0, 5, "begin") == 0)
      return 0;

    if (str.compare(0, 3, "end") == 0)
      return 1;

    if (str.compare(0, 4, "mark") == 0)
      return 2;

    return -1;
  }

  bool C_Interpreter::getEndOperator(int type, std::string str)
  {
    switch(type)
    {
      case -1:
        return (str[str.size() - 1] == ':') || (str[str.size() - 1] == '.') || (str[str.size() - 1] == ';');
        break;
      case 0:
        return str[str.size() - 1] == ':';
        break;
      case 1:
        return str[str.size() - 1] == '.';
        break;
      case 2:
        return str[str.size() - 1] == ';';
        break;
      default:
        return str[str.size() - 1] == ';';
        break;
    }
  }

  C_Interpreter::~C_Interpreter()
  {

  }

}
