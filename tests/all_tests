#include "gtest.h"
#include "../TTable/TScanTable.h"
#include "../TTable/TSortTable.h"
#include "../TTable/ArrayHashTable.h"

TEST(TScanTable, CAN_CREATE_TABLE)
{
    TTable<int, int>* s;
    s = new TScanTable<int, int>;
    SUCCEED();
}

TEST(TScanTable, CAN_SET_GET_CURRENT_REC)
{
    TTable<int, int>* s;
    s = new TScanTable<int, int>;
    EXPECT_ANY_THROW(s->getCurrRec());
    TRecord<int, int> rec1(1, 3), rec2;
    EXPECT_NO_THROW(s->setCurrPos(0));
    EXPECT_NO_THROW(s->setRec(rec1));
    rec2 = s->getCurrRec();
    EXPECT_EQ(rec1 == rec2, 1);
}

TEST(TScanTable, FULL_TABLE)
{
    TTable<int, int>* s;
    s = new TScanTable<int, int>(1);
    EXPECT_FALSE(s->isFull());
    int r = s->ins(3, 100);
    EXPECT_TRUE(s->isFull());
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TScanTable, END_TABLE)
{
    TTable<int, int>* s;
    s = new TScanTable<int, int>;
    EXPECT_FALSE(s->isEnd());
    int r = s->ins(3, 100);
    s->setCurrPos(1);
    EXPECT_TRUE(s->isEnd());
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TScanTable, CAN_INSERT_RECORD) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    EXPECT_NO_THROW(s->ins(rec));
    EXPECT_EQ(s->getCurrPos(), 0);
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TScanTable, CANNOT_INSERT_RECORD_IF_FULL) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(1);
    TRecord<int, int> rec1 = { 1, 100 };
    TRecord<int, int> rec2 = { 2, 200 };
    int r = s->ins(rec1);
    EXPECT_ANY_THROW(s->ins(rec2));
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TScanTable, CAN_FIND_RECORD) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    s->ins(rec);
    EXPECT_TRUE(s->find(1));
    EXPECT_EQ(s->getEff(), 2);
}

TEST(TScanTable, CANNOT_FIND_NON_EXISTENT_RECORD) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    s->ins(rec);
    EXPECT_FALSE(s->find(2));
    EXPECT_EQ(s->getEff(), 2);
}

TEST(TScanTable, CAN_DELETE_RECORD) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>;
    TRecord<int, int> rec1 = { 1, 100 };
    TRecord<int, int> rec2 = { 2, 200 };
    s->ins(rec1);
    s->ins(rec2);
    EXPECT_NO_THROW(s->del(1));
    EXPECT_FALSE(s->find(1));
    EXPECT_EQ(s->getEff(), 6);
}

TEST(TScanTable, CANNOT_DELETE_NON_EXISTENT_RECORD) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    s->ins(rec);
    EXPECT_ANY_THROW(s->del(2));
    EXPECT_EQ(s->getEff(), 2);
}

TEST(TScanTable, CANNOT_INSERT_EXISTING_RECORD) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    s->ins(rec);
    EXPECT_ANY_THROW(s->ins(rec));
    EXPECT_EQ(s->getEff(), 2);
}

TEST(TScanTable, CANNOT_DELETE_FROM_EMPTY_TABLE) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(1);
    EXPECT_ANY_THROW(s->del(1));
}

TEST(TScanTable, CAN_CR_TABLE) {
    TTable<int, int>* s;
    s = new TScanTable<int, int>(6);
    s->ins({ 5, 500 });
    s->ins({ 3, 300 });
    s->ins({ 4, 400 });
    s->ins({ 1, 100 });
    EXPECT_TRUE(s->find(1));
    EXPECT_EQ(s->getCurrPos(), 3);
    EXPECT_TRUE(s->find(3));
    EXPECT_EQ(s->getCurrPos(), 1);
    EXPECT_TRUE(s->find(4));
    EXPECT_EQ(s->getCurrPos(), 2);
    EXPECT_TRUE(s->find(5));
    EXPECT_EQ(s->getCurrPos(), 0);
    EXPECT_EQ(s->getEff(), 20);
}



TEST(TSortTable, CAN_CREATE_SORT_TABLE) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>;
    SUCCEED();
}

TEST(TSortTable, FULL_TABLE)
{
    TTable<int, int>* s;
    s = new TSortTable<int, int>(1);
    EXPECT_FALSE(s->isFull());
    int r = s->ins(3, 100);
    EXPECT_TRUE(s->isFull());
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TSortTable, END_TABLE)
{
    TTable<int, int>* s;
    s = new TSortTable<int, int>(6);
    EXPECT_FALSE(s->isEnd());
    int r = s->ins(3, 100);
    s->setCurrPos(1);
    EXPECT_TRUE(s->isEnd());
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TSortTable, CAN_INSERT_RECORD) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>;
    TRecord<int, int> rec = { 3, 300 };
    EXPECT_NO_THROW(s->ins(rec));
    EXPECT_EQ(s->getCurrPos(), 0);
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TSortTable, CANNOT_INSERT_RECORD_IF_FULL) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(1);
    TRecord<int, int> rec1 = { 1, 100 };
    TRecord<int, int> rec2 = { 2, 200 };
    s->ins(rec1);
    EXPECT_ANY_THROW(s->ins(rec2));
    EXPECT_EQ(s->getEff(), 1);
}

TEST(TSortTable, CAN_FIND_RECORD) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(5);
    TRecord<int, int> rec = { 2, 200 };
    s->ins(rec);
    EXPECT_TRUE(s->find(2));
    EXPECT_EQ(s->getCurrKey(), 2);
    EXPECT_EQ(s->getEff(), 2);
}

TEST(TSortTable, CANNOT_FIND_NON_EXISTENT_RECORD) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(5);
    TRecord<int, int> rec = { 3, 300 };
    s->ins(rec);
    EXPECT_FALSE(s->find(4));
    EXPECT_EQ(s->getEff(), 3);
}

TEST(TSortTable, CAN_DELETE_RECORD) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(5);
    TRecord<int, int> rec1 = { 1, 100 };
    TRecord<int, int> rec2 = { 2, 200 };
    s->ins(rec1);
    s->ins(rec2);
    EXPECT_NO_THROW(s->del(1));
    EXPECT_FALSE(s->find(1));
    EXPECT_EQ(s->getEff(), 8);
}

TEST(TSortTable, CANNOT_DELETE_NON_EXISTENT_RECORD) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    s->ins(rec);
    EXPECT_ANY_THROW(s->del(2));
    EXPECT_EQ(s->getEff(), 3);
}

TEST(TSortTable, CANNOT_INSERT_EXISTING_RECORD) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    s->ins(rec);
    EXPECT_ANY_THROW(s->ins(rec));
    EXPECT_EQ(s->getEff(), 2);
}

TEST(TSortTable, CANNOT_DELETE_FROM_EMPTY_TABLE) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>;
    EXPECT_ANY_THROW(s->del(1));
    EXPECT_EQ(s->getEff(), 0);
}

TEST(TSortTable, CAN_SORT_TABLE_WITH_QSORT) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(6);
    s->ins({ 5, 500 });
    s->ins({ 3, 300 });
    s->ins({ 4, 400 });
    s->ins({ 1, 100 });
    s->QSort();
    EXPECT_TRUE(s->find(1));
    EXPECT_EQ(s->getCurrPos(), 0);
    EXPECT_TRUE(s->find(3));
    EXPECT_EQ(s->getCurrPos(), 1);
    EXPECT_TRUE(s->find(4));
    EXPECT_EQ(s->getCurrPos(), 2);
    EXPECT_TRUE(s->find(5));
    EXPECT_EQ(s->getCurrPos(), 3);
    EXPECT_EQ(s->getEff(), 33);
}

TEST(TSortTable, CAN_SORT_TABLE_WITH_SELECT_SORT) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>(6);
    s->ins({ 5, 500 });
    s->ins({ 3, 300 });
    s->ins({ 4, 400 });
    s->ins({ 1, 100 });
    s->SelectSort();
    EXPECT_TRUE(s->find(1));
    EXPECT_EQ(s->getCurrPos(), 0);
    EXPECT_TRUE(s->find(3));
    EXPECT_EQ(s->getCurrPos(), 1);
    EXPECT_TRUE(s->find(4));
    EXPECT_EQ(s->getCurrPos(), 2);
    EXPECT_TRUE(s->find(5));
    EXPECT_EQ(s->getCurrPos(), 3);
    EXPECT_EQ(s->getEff(), 41);
}

/*TEST(TSortTable, CAN_SORT_TABLE_WITH_MERGE_SORT) {
    TTable<int, int>* s;
    s = new TSortTable<int, int>;
    s->ins({ 5, 500 });
    s->ins({ 3, 300 });
    s->ins({ 4, 400 });
    s->ins({ 1, 100 });
    s->MergeSort(0,3);
    EXPECT_TRUE(s->find(1));
    EXPECT_EQ(s->getCurrPos(), 0);
    EXPECT_TRUE(s->find(3));
    EXPECT_EQ(s->getCurrPos(), 1);
    EXPECT_TRUE(s->find(4));
    EXPECT_EQ(s->getCurrPos(), 2);
    EXPECT_TRUE(s->find(5));
    EXPECT_EQ(s->getCurrPos(), 3);
}*/


TEST(ArrayHashTable, CAN_CREATE_ARRAY_HASH_TABLE) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    SUCCEED();
}

TEST(ArrayHashTable, FULL_TABLE)
{
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>(1);
    EXPECT_FALSE(h->isFull());
    h->ins(3, 100);
    EXPECT_TRUE(h->isFull());
    EXPECT_EQ(h->getEff(), 3);
}

TEST(ArrayHashTable, END_TABLE)
{
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>(1);
    EXPECT_FALSE(h->isEnd());
}

TEST(ArrayHashTable, CAN_INSERT_RECORD) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>(5);
    TRecord<int, int> rec = { 1, 100 };
    EXPECT_NO_THROW(h->ins(rec));
    EXPECT_TRUE(h->find(1));
    EXPECT_EQ(h->getEff(), 5);
}

TEST(ArrayHashTable, CANNOT_INSERT_DUPLICATE_KEY) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    TRecord<int, int> rec = { 1, 100 };
    h->ins(rec);
    EXPECT_ANY_THROW(h->ins(rec));
    EXPECT_EQ(h->getEff(), 5);
}

TEST(ArrayHashTable, CAN_FIND_RECORD) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    TRecord<int, int> rec = { 2, 200 };
    h->ins(rec);
    EXPECT_TRUE(h->find(2));
    EXPECT_EQ(h->getEff(), 5);
}

TEST(ArrayHashTable, CANNOT_FIND_NON_EXISTENT_RECORD) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    TRecord<int, int> rec = { 3, 300 };
    h->ins(rec);
    EXPECT_FALSE(h->find(4));
    EXPECT_EQ(h->getEff(), 5);
}

TEST(ArrayHashTable, CAN_DELETE_RECORD) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    TRecord<int, int> rec = { 4, 400 };
    h->ins(rec);
    EXPECT_NO_THROW(h->del(4));
    EXPECT_FALSE(h->find(4));
    EXPECT_EQ(h->getEff(), 9);
}

TEST(ArrayHashTable, CANNOT_DELETE_NON_EXISTENT_RECORD) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    TRecord<int, int> rec = { 5, 500 };
    h->ins(rec);
    EXPECT_ANY_THROW(h->del(6));
    EXPECT_EQ(h->getEff(), 5);
}

TEST(ArrayHashTable, CAN_HANDLE_DELETED_RECORD) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    TRecord<int, int> rec1 = { 1, 100 };
    TRecord<int, int> rec2 = { 2, 200 };
    h->ins(rec1);
    h->ins(rec2);
    EXPECT_NO_THROW(h->del(1));
    EXPECT_TRUE(h->find(2));
    EXPECT_FALSE(h->find(1));
    EXPECT_EQ(h->getEff(), 14);
}

TEST(ArrayHashTable, CAN_USE_RESET_AND_GO_NEXT) {
    TTable<int, int>* h;
    h = new ArrayHashTable<int, int>;
    h->ins({ 1, 100 });
    h->ins({ 2, 200 });
    h->reset();
    EXPECT_FALSE(h->isEnd());
    EXPECT_EQ(h->getCurrKey(), 1);
    h->goNext();
    EXPECT_EQ(h->getCurrKey(), 2);
    EXPECT_EQ(h->getEff(), 8);
}