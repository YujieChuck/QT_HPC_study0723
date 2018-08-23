/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Interface_TYPES_H
#define Interface_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace UpdateService {

class FileData;

class VersionInfo;


class FileData : public virtual ::apache::thrift::TBase {
 public:

  FileData(const FileData&);
  FileData& operator=(const FileData&);
  FileData() : strFileName(), buff() {
  }

  virtual ~FileData() throw();
  std::string strFileName;
  std::string buff;

  void __set_strFileName(const std::string& val);

  void __set_buff(const std::string& val);

  bool operator == (const FileData & rhs) const
  {
    if (!(strFileName == rhs.strFileName))
      return false;
    if (!(buff == rhs.buff))
      return false;
    return true;
  }
  bool operator != (const FileData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(FileData &a, FileData &b);

inline std::ostream& operator<<(std::ostream& out, const FileData& obj)
{
  obj.printTo(out);
  return out;
}


class VersionInfo : public virtual ::apache::thrift::TBase {
 public:

  VersionInfo(const VersionInfo&);
  VersionInfo& operator=(const VersionInfo&);
  VersionInfo() : uniqueFlag(), title(), updateTime(), updateInfo() {
  }

  virtual ~VersionInfo() throw();
  std::string uniqueFlag;
  std::string title;
  std::string updateTime;
  std::string updateInfo;

  void __set_uniqueFlag(const std::string& val);

  void __set_title(const std::string& val);

  void __set_updateTime(const std::string& val);

  void __set_updateInfo(const std::string& val);

  bool operator == (const VersionInfo & rhs) const
  {
    if (!(uniqueFlag == rhs.uniqueFlag))
      return false;
    if (!(title == rhs.title))
      return false;
    if (!(updateTime == rhs.updateTime))
      return false;
    if (!(updateInfo == rhs.updateInfo))
      return false;
    return true;
  }
  bool operator != (const VersionInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const VersionInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(VersionInfo &a, VersionInfo &b);

inline std::ostream& operator<<(std::ostream& out, const VersionInfo& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif
