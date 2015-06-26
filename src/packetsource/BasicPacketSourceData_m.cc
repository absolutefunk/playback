//
// Generated file, do not edit! Created by nedtool 4.6 from packetsource/BasicPacketSourceData.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BasicPacketSourceData_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(BasicPacketSourceData);

BasicPacketSourceData::BasicPacketSourceData(const char *name, int kind) : ::cMessage(name,kind)
{
    this->srcPort_var = 0;
    this->destPort_var = 0;
    this->srcAddress_var = 0;
    this->destAddress_var = 0;
    this->seqNo_var = 0;
    this->windowSize_var = 0;
}

BasicPacketSourceData::BasicPacketSourceData(const BasicPacketSourceData& other) : ::cMessage(other)
{
    copy(other);
}

BasicPacketSourceData::~BasicPacketSourceData()
{
}

BasicPacketSourceData& BasicPacketSourceData::operator=(const BasicPacketSourceData& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void BasicPacketSourceData::copy(const BasicPacketSourceData& other)
{
    this->srcPort_var = other.srcPort_var;
    this->destPort_var = other.destPort_var;
    this->srcAddress_var = other.srcAddress_var;
    this->destAddress_var = other.destAddress_var;
    this->seqNo_var = other.seqNo_var;
    this->windowSize_var = other.windowSize_var;
}

void BasicPacketSourceData::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->srcPort_var);
    doPacking(b,this->destPort_var);
    doPacking(b,this->srcAddress_var);
    doPacking(b,this->destAddress_var);
    doPacking(b,this->seqNo_var);
    doPacking(b,this->windowSize_var);
}

void BasicPacketSourceData::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->srcPort_var);
    doUnpacking(b,this->destPort_var);
    doUnpacking(b,this->srcAddress_var);
    doUnpacking(b,this->destAddress_var);
    doUnpacking(b,this->seqNo_var);
    doUnpacking(b,this->windowSize_var);
}

short BasicPacketSourceData::getSrcPort() const
{
    return srcPort_var;
}

void BasicPacketSourceData::setSrcPort(short srcPort)
{
    this->srcPort_var = srcPort;
}

short BasicPacketSourceData::getDestPort() const
{
    return destPort_var;
}

void BasicPacketSourceData::setDestPort(short destPort)
{
    this->destPort_var = destPort;
}

const char * BasicPacketSourceData::getSrcAddress() const
{
    return srcAddress_var.c_str();
}

void BasicPacketSourceData::setSrcAddress(const char * srcAddress)
{
    this->srcAddress_var = srcAddress;
}

const char * BasicPacketSourceData::getDestAddress() const
{
    return destAddress_var.c_str();
}

void BasicPacketSourceData::setDestAddress(const char * destAddress)
{
    this->destAddress_var = destAddress;
}

int BasicPacketSourceData::getSeqNo() const
{
    return seqNo_var;
}

void BasicPacketSourceData::setSeqNo(int seqNo)
{
    this->seqNo_var = seqNo;
}

int BasicPacketSourceData::getWindowSize() const
{
    return windowSize_var;
}

void BasicPacketSourceData::setWindowSize(int windowSize)
{
    this->windowSize_var = windowSize;
}

class BasicPacketSourceDataDescriptor : public cClassDescriptor
{
  public:
    BasicPacketSourceDataDescriptor();
    virtual ~BasicPacketSourceDataDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BasicPacketSourceDataDescriptor);

BasicPacketSourceDataDescriptor::BasicPacketSourceDataDescriptor() : cClassDescriptor("BasicPacketSourceData", "cMessage")
{
}

BasicPacketSourceDataDescriptor::~BasicPacketSourceDataDescriptor()
{
}

bool BasicPacketSourceDataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BasicPacketSourceData *>(obj)!=NULL;
}

const char *BasicPacketSourceDataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BasicPacketSourceDataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int BasicPacketSourceDataDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *BasicPacketSourceDataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcPort",
        "destPort",
        "srcAddress",
        "destAddress",
        "seqNo",
        "windowSize",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int BasicPacketSourceDataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcPort")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPort")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddress")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddress")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNo")==0) return base+4;
    if (fieldName[0]=='w' && strcmp(fieldName, "windowSize")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BasicPacketSourceDataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "short",
        "short",
        "string",
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *BasicPacketSourceDataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int BasicPacketSourceDataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BasicPacketSourceData *pp = (BasicPacketSourceData *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BasicPacketSourceDataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BasicPacketSourceData *pp = (BasicPacketSourceData *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrcPort());
        case 1: return long2string(pp->getDestPort());
        case 2: return oppstring2string(pp->getSrcAddress());
        case 3: return oppstring2string(pp->getDestAddress());
        case 4: return long2string(pp->getSeqNo());
        case 5: return long2string(pp->getWindowSize());
        default: return "";
    }
}

bool BasicPacketSourceDataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BasicPacketSourceData *pp = (BasicPacketSourceData *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcPort(string2long(value)); return true;
        case 1: pp->setDestPort(string2long(value)); return true;
        case 2: pp->setSrcAddress((value)); return true;
        case 3: pp->setDestAddress((value)); return true;
        case 4: pp->setSeqNo(string2long(value)); return true;
        case 5: pp->setWindowSize(string2long(value)); return true;
        default: return false;
    }
}

const char *BasicPacketSourceDataDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *BasicPacketSourceDataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BasicPacketSourceData *pp = (BasicPacketSourceData *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


