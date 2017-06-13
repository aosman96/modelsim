#ifndef _RTTI_H
#define _RTTI_H

#define is_a(obj,class__) dynamic_cast<class__*>(obj)!=NULL
#define is_not_a(obj,class__) dynamic_cast<class__*>(obj)==NULL

#endif