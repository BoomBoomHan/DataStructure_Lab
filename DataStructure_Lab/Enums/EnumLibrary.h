#pragma once

enum ETraversalMethod
{
    /**
     *顺序
     */
    Sequential,
    /**
     *倒叙
     */
    Inverted
};

enum ELinkNodeEqual
{
    /**
     *值相等
     */
    ValueRequired,
    /**
     *Last指针域相等
     */
    LastPtrRequired,
    /**
     *Next指针域相等
     */
    NextPtrRequired
};