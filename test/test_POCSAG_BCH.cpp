#include "Arduino.h"
#include "unity.h"
#include "BCH.h"
#include "POCSAG.h"

POCSAG poc;



void test_bch_code_correction(){

    //2 bit secure error code correction (should work) (without parity check)
    ArrayList<unsigned long> * pocsagcodeunsecure = poc.tryCodeErrorCorrection(0b01111010100010011100000110010000, true);

    //check if the code correction was successful
    TEST_ASSERT_EQUAL_UINT32(0b01111010100010011100000110010111, pocsagcodeunsecure->getArray()[0]);

    //free the memory of the array and the object
    pocsagcodeunsecure->deleteObject();


    //2 bit secure error code correction (should not work) (with with parity check) (wrong parity)
    pocsagcodeunsecure = poc.tryCodeErrorCorrection(0b01111010100010011100000110010000, true, true);

    //check if the code correction was successful
    TEST_ASSERT_EQUAL_UINT32(0, pocsagcodeunsecure->getSize());


    //free the memory of the array and the object
    pocsagcodeunsecure->deleteObject();


    //2 bit unsecure code correction (should not work) (too many errors)
    pocsagcodeunsecure = poc.tryCodeErrorCorrection(0b01111010100010011100000110011001, true, false);

    //check if the array contains values (should be 0)
    TEST_ASSERT_EQUAL_UINT32(0, pocsagcodeunsecure->getSize());

    //free the memory of the array and the object
    pocsagcodeunsecure->deleteObject();


    //3 bit unsecure code correction (should work) (with parity check)
    pocsagcodeunsecure = poc.tryUnsecureCodeErrorCorrection(0b01111010100010011100101110010101, 3);

    //check if the code correction was successful
    TEST_ASSERT_EQUAL_UINT32(0b01111010100010011100000110010111, pocsagcodeunsecure->getArray()[0]);
    TEST_ASSERT_EQUAL_UINT32(1, pocsagcodeunsecure->getSize());

    //free the memory of the array and the object
    pocsagcodeunsecure->deleteObject();


    //3 bit unsecure code correction (should not work) (with parity check) (wrong parity)
    pocsagcodeunsecure = poc.tryUnsecureCodeErrorCorrection(0b01111010100010011101000110011010, 3);

    //check if the code correction was successful
    TEST_ASSERT_EQUAL_UINT32(0, pocsagcodeunsecure->getSize());

    //free the memory of the array and the object
    pocsagcodeunsecure->deleteObject();

}

void test_bch_memoryleak(){
    //read the free heap memory and store it in heapBeforCreation
    size_t heapBeforCreation = heap_caps_get_free_size(MALLOC_CAP_8BIT);

    //run the error correction and store the pointer to the result in pocsagcodeunsecure
    ArrayList<unsigned long> * pocsagcodeunsecure = poc.tryUnsecureCodeErrorCorrection(0b01111010100010011100000110010000, 3);

    //free the memory of the array and the object
    pocsagcodeunsecure->deleteObject();

    //read the free heap memory after the object is deleted and store it in heapAfterDeletion
    size_t heapAfterDeletion = heap_caps_get_free_size(MALLOC_CAP_8BIT);

    //calculate the leaked memory (free heap memory before the creation minus the free heap memory after the deletion) and print in
    //difference should be zero (not sure if UINT32 is the right value)
    TEST_ASSERT_EQUAL_UINT32(0, heapBeforCreation - heapAfterDeletion);

}

void setup(){
    delay(2000);
    UNITY_BEGIN();    // IMPORTANT LINE!

    //test the bch for memory leaks
    RUN_TEST(test_bch_memoryleak);

    //test if the correction is sucessful
    RUN_TEST(test_bch_code_correction);

    UNITY_END(); // stop unit testing
}


void loop(){

}
