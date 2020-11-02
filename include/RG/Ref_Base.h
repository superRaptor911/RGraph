/**
 * @file Ref_Base.h
 * @author Aditya Aravind (raptor.inc2018@gmail.com)
 * @brief Base class for keeping count of references.
 * @version 0.1
 * @date 22-07-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef REF_BASE_H
#define REF_BASE_H

#include <RG/Global_Def.h>
#include <cstdio>

namespace rg
{
    class Ref_Base
    {
    private:
        int *m_ref_count = nullptr;
    protected:

        /**
         * @brief Start ref counting
         * 
         */
        void startRefCounting()
        {
            if (m_ref_count != nullptr)
                printf("Error : _ref_count not null!. Memory leak detected\n");
            
            m_ref_count = new int;
            PTR_VAL(m_ref_count) = 1;
        }

        /**
         * @brief De-attach from ref count. 
         * 
         * @return true if ref_count reaches 0
         * @return false otherwise
         */
        bool dettachRefCount()
        {
            if (m_ref_count == nullptr)
            {
                printf("Error::REF_BASE: dettaching from null ref!. Op failed Memory will leak\n");
                return false;
            }
            
            PTR_VAL(m_ref_count) -= 1;

            // Delete ptr
            if (PTR_VAL(m_ref_count) == 0)
            {
                delete m_ref_count;
                m_ref_count = nullptr;
                return true;
            }

            m_ref_count = nullptr;
            return false;
        }

        /**
         * @brief Attach to another ref count. make sure that our ref count should be deattached.
         * 
         * 
         * @param ref ptr
         */
        void attachRefCount(const Ref_Base &ref)
        {
            if (m_ref_count != nullptr)
                printf("Error::REF_BASE: _ref_count not null!. Memory leak detected while attaching\n");

            if (ref.m_ref_count == nullptr)
            {
                printf("Error::REF_BASE: attaching to null ref!. Op failed Memory will leak\n");
                return;
            }

            // Attach to ref
            m_ref_count = ref.m_ref_count;
            // increment count by 1
            PTR_VAL(m_ref_count) += 1;
        }

    };
    
}

#endif
