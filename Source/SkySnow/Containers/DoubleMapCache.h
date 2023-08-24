//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by liuqian(SkySnow),zhangshuangxue(Calence)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#pragma once
#include <unordered_map>
#include "ThreadMutex.h"
#include "HashUtil.h"
namespace SkySnow
{
    //ThreadSafe
    //find: 先查主表，主表查到，返回value；主表未查到，查副表
    //     副表查到，返回value(同时将key-value移动到主表，
    //     副表移除key-value)
    //     副表未查到，返回空
    //add: 添加到主表中
    //Discard: 清空副表，将主表数据交换到副表，主表此时为空
    //         如果频繁调用swap，那么key-value的生命周期会变短
    //使用读写锁，线程安全;使用哈希表，查找是常数
    template<typename MapKey,typename MapValue>
    class DoubleMapCache
    {
    public:
        using Hash_fun = HMapHashFn<MapKey>;
        typedef std::unordered_map<MapKey, MapValue,Hash_fun> SNMap;
        DoubleMapCache()
        {
            _MainMap.clear();
            _BackMap.clear();
        }
        int Size()
        {
            _RWLock.ReadLock();
            int size = _MainMap.size() + _BackMap.size();
            _RWLock.ReadUnLock();
            return size;
        }
        bool Find(const MapKey& key,MapValue& out)
        {
            _RWLock.WriteLock();
            bool find_flag = false;
            //先查主表
            auto main_iter = _MainMap.find(key);
            if(main_iter != _MainMap.end())
            {
                out = main_iter->second;
                find_flag = true;
            }
            //主表未查到,查副表
            if(!find_flag)
            {
                auto back_iter = _BackMap.find(key);
                if(back_iter != _BackMap.end())
                {
                    out = back_iter->second;
                    _MainMap[key] = out;
                    _BackMap.erase(back_iter);
                    find_flag = true;
                }
            }
            _RWLock.WriteUnlock();
            return find_flag;
        }
        //添加key-value，主表中没有就添加，主表中有返回false(可能其它线程添加进去了,find会查找到)
        bool Add(const MapKey& key,const MapValue& value)
        {
            _RWLock.WriteLock();
            bool find_flag = false;
            auto main_iter = _MainMap.find(key);
            if(main_iter == _MainMap.end())
            {
                _MainMap[key] = value;
                find_flag = true;
            }
            _RWLock.WriteUnlock();
            return find_flag;
        }
        //先清空副表，接着交换主表数据到副表中
        //如果连续调用两次，将会把主表与副表全部清空
        bool Discard()
        {
            _RWLock.WriteLock();
            _BackMap.clear();
            _BackMap.swap(_MainMap);
            _RWLock.WriteUnlock();
            return true;
        }
    private:
        ThreadRWMutex   _RWLock;
        SNMap           _MainMap;
        SNMap           _BackMap;
    };
}
