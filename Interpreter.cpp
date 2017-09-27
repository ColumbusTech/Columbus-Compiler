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
    if (mInited == false)
      return false;

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
          if (getAfterTypes(line))
            continue;
        }

        bool endType = false;

        if (line[line.size() - 1] == ':' || line[line.size() - 1] == ';' || line[line.size() - 1] == '.')
          endType = true;

        C_Type type;
        if (!endType)
          type.type = getType(line);
        else
          type.type = getType(line.substr(0, line.size() - 1));
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

      if (mTypes[i].afterTypeI == -10000)
      {
        switch (mTypes[i].type)
        {
          case 0:
            break;
          case 1:
            break;
          case 2:
            break;
          case 3:
            break;
          case 4:
            break;
          case 5:
            break;
          case 6:
            C_Error("%s: %i: expected [port number] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            ret = false;
            break;
          case 7:
            C_Error("%s: %i: expected [port number] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            ret = false;
            break;
        }
      }

      if (mTypes[i].afterTypeS.empty())
      {
        switch (mTypes[i].type)
        {
          case 0:
            break;
          case 1:
            break;
          case 2:
            C_Error("%s: %i: expected [mark] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            ret = false;
            break;
          case 3:
            C_Error("%s: %i: expected [mark] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            ret = false;
          case 4:
            C_Error("%s: %i: expected [port] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            ret = false;
          case 5:
            C_Error("%s: %i: expected [port] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            ret = false;
            break;
          case 6:
            C_Error("%s: %i: expected [port] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
          case 7:
            C_Error("%s: %i: expected [port] `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
        }
      }

      if (mTypes[i].type == 3)
      {
        if (std::count(mMarks.begin(), mMarks.end(), mTypes[i].afterTypeS) == 0)
        {
          C_Error("%s: %i: undefined mark `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].afterTypeS.c_str());
          ret = false;
        }
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
            file << "org 0" << std::endl << std::endl;

          if (mTypes[i].afterType == true)
            file << "org " << mTypes[i].afterTypeI << std::endl << std::endl;

          break;
        };
        case 1:
        {
          file << std::endl << "end" << std::endl;
          break;
        };
        case 2:
        {
          file << mTypes[i].afterTypeS << ':' << std::endl;
          break;
        };
        case 3:
        {
          file << "goto " << mTypes[i].afterTypeS << std::endl;
          break;
        };
        case 4:
        {
          file << "clrf " << mTypes[i].afterTypeS << std::endl;
          break;
        };
        case 5:
        {
          file << "movlw 0xff" << std::endl;
          file << "movwf " << mTypes[i].afterTypeS << std::endl;
          break;
        };
        case 6:
        {
          file << "bcf " << mTypes[i].afterTypeS << ", " << mTypes[i].afterTypeI << std::endl;
          break;
        };
        case 7:
        {
          file << "bsf " << mTypes[i].afterTypeS << ", " << mTypes[i].afterTypeI << std::endl;
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

  bool C_Interpreter::getAfterTypes(std::string line)
  {
    ////////////////////////////////////////////
    if (mTypes.back().type == 0)
    {
      if (line[0] == ':')
      {
        mTypes.back().endOperator = true;
        mTypes.back().afterType = false;
        mTypes.back().afterTypeI = 0;

        return true;
      } else if(isStringNumber(line) || isStringNumber(line.substr(0, line.size() - 1)))
      {
        mTypes.back().afterType = true;
        mTypes.back().afterTypeI = atoi(line.c_str());

        if (line[line.size() - 1] == ':')
          mTypes.back().endOperator = true;

        return true;
      }
    }
    ////////////////////////////////////////////
    if (mTypes.back().type == 1)
    {
      if (line[0] == '.')
      {
        mTypes.back().endOperator = true;
        return true;
      }
    }
    ////////////////////////////////////////////
    if (mTypes.back().type == 2)
    {
      if (line[0] == ';')
      {
        mTypes.back().endOperator = true;
          return true;
      }

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

        mMarks.push_back(mTypes.back().afterTypeS);

        return true;
      }
    }
    ////////////////////////////////////////////
    if (mTypes.back().type == 3 || mTypes.back().type == 4 || mTypes.back().type == 5)
    {
      if (line[0] == ';')
      {
        mTypes.back().endOperator = true;
          return true;
      }

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

        return true;
      }
    }
    ////////////////////////////////////////////
    if (mTypes.back().type == 6 || mTypes.back().type == 7)
    {
      if (mTypes.back().afterTypeI == -10000)
      {
        if (line[line.size() - 1] == ';')
        {
          mTypes.back().endOperator = true;
          if (isStringNumber(line.substr(0, line.size() - 1)))
            mTypes.back().afterTypeI = atoi(line.substr(0, line.size() - 1).c_str());
          else
            mTypes.back().afterTypeS = line.substr(0, line.size() - 1);
        } else
        {
          if (isStringNumber(line))
            mTypes.back().afterTypeI = atoi(line.c_str());
          else
            mTypes.back().afterTypeS = line;
        }

        return true;
      }
    }
    ////////////////////////////////////////////

    return false;
  }

  bool C_Interpreter::isStringNumber(std::string str)
  {
    return !str.empty() && std::find_if(str.begin(),
        str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
  }

  int C_Interpreter::getType(std::string str)
  {
    if (str.compare(mSyntax.find(0)->second) == 0)
      return 0;

    if (str.compare(mSyntax.find(1)->second) == 0)
      return 1;

    if (str.compare(mSyntax.find(2)->second) == 0)
      return 2;

    if (str.compare(mSyntax.find(3)->second) == 0)
      return 3;

    if (str.compare(mSyntax.find(4)->second) == 0)
      return 4;

    if (str.compare(mSyntax.find(5)->second) == 0)
      return 5;

    if (str.compare(mSyntax.find(6)->second) == 0)
      return 6;

    if (str.compare(mSyntax.find(7)->second) == 0)
      return 7;

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
      case 3:
        return str[str.size() - 1] == ';';
        break;
      case 4:
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
