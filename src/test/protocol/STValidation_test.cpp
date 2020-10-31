

#include <ripple/basics/Log.h>
#include <ripple/protocol/jss.h>
#include <ripple/protocol/SecretKey.h>
#include <ripple/protocol/st.h>
#include <ripple/json/json_reader.h>
#include <ripple/json/to_string.h>
#include <ripple/beast/unit_test.h>
#include <test/jtx.h>

#include <memory>
#include <type_traits>

namespace ripple {

class STValidation_test : public beast::unit_test::suite
{
public:
    void testDeserialization ()
    {
        testcase ("Deserialization");

        constexpr std::uint8_t payload1[] =
        {
            0x22, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x51,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x73,
            0x21, 0xed, 0x78, 0x00, 0xe6, 0x73, 0x00, 0x72, 0x00, 0x3c, 0x00,
            0x00, 0x00, 0x88, 0x00, 0xe6, 0x73, 0x38, 0x00, 0x00, 0x8a, 0x00,
            0x88, 0x4e, 0x31, 0x30, 0x5f, 0x5f, 0x63, 0x78, 0x78, 0x61, 0x62,
            0x69
        };

        constexpr std::uint8_t payload2[] =
        {
            0x22, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x51,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x73,
            0x21, 0xed, 0xff, 0x03, 0x1c, 0xbe, 0x65, 0x22, 0x61, 0x9c, 0x5e,
            0x13, 0x12, 0x00, 0x3b, 0x43, 0x00, 0x00, 0x00, 0xf7, 0x3f, 0x3f,
            0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x13, 0x13, 0x13, 0x3a, 0x27,
            0xff
        };

        constexpr std::uint8_t payload3[] =
        {
            0x22, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x51,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a
        };

        try
        {
            SerialIter sit {payload1};
            auto stx = std::make_shared<ripple::STValidation>(sit,
                [](PublicKey const& pk) {
                    return calcNodeID(pk);
                }, false);
            fail("An exception should have been thrown");
        }
        catch (std::exception const& e)
        {
            BEAST_EXPECT(strcmp(e.what(),
                "Invalid public key in validation") == 0);
        }

        try
        {
            SerialIter sit {payload2};
            auto stx = std::make_shared<ripple::STValidation>(sit,
                [](PublicKey const& pk) {
                    return calcNodeID(pk);
                }, false);
            fail("An exception should have been thrown");
        }
        catch (std::exception const& e)
        {
            BEAST_EXPECT(strcmp(e.what(),
                "Invalid public key in validation") == 0);
        }

        try
        {
            SerialIter sit {payload3};
            auto stx = std::make_shared<ripple::STValidation>(sit,
                [](PublicKey const& pk) {
                    return calcNodeID(pk);
                }, false);
            fail("An exception should have been thrown");
        }
        catch (std::exception const& e)
        {
            BEAST_EXPECT(strcmp(e.what(),
                "Field 'SigningPubKey' is required but missing.") == 0);
        }
    }

    void
    run() override
    {
        testDeserialization();
    }
};

BEAST_DEFINE_TESTSUITE(STValidation,protocol,ripple);

} 






