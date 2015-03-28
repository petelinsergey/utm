#include "stdafx.h"
#include "md5.h"

#include "uhex.h"

#include "ubase_test.h"

namespace utm {

md5_context::md5_context(void)
{
    total[0] = 0;
    total[1] = 0; 

    state[0] = 0x67452301;
    state[1] = 0xEFCDAB89;
    state[2] = 0x98BADCFE;
	state[3] = 0x10325476;
}

md5_context::~md5_context(void)
{
}

md5_result::md5_result(void)
{
	as_string[0] = 0;
	as_string[32] = 0;
}

md5_result::~md5_result(void)
{

}

namespace md5 {

    #define  GET_UINT32(n,b,i)                       \
    {                                               \
        (n) = ( (uint32) (b)[(i)    ]       )       \
            | ( (uint32) (b)[(i) + 1] <<  8  )       \
            | ( (uint32) (b)[(i) + 2] << 16  )       \
            | ( (uint32) (b)[(i) + 3] << 24  );      \
    }

    #define  PUT_UINT32(n,b,i)                       \
    {                                               \
        (b)[(i)    ] = (uint8) ( (n)       );       \
        (b)[(i) + 1] = (uint8) ( (n) >>  8  );       \
        (b)[(i) + 2] = (uint8) ( (n) >> 16  );       \
        (b)[(i) + 3] = (uint8) ( (n) >> 24  );       \
    }

    void md5_process( md5_context *ctx, const uint8 data[64 ] )
    {
        uint32 X[ 16 ], A, B, C, D;

        GET_UINT32( X[ 0],  data,  0  );
        GET_UINT32( X[ 1],  data,  4  );
        GET_UINT32( X[ 2],  data,  8  );
        GET_UINT32( X[ 3],  data, 12  );
        GET_UINT32( X[ 4],  data, 16  );
        GET_UINT32( X[ 5],  data, 20  );
        GET_UINT32( X[ 6],  data, 24  );
        GET_UINT32( X[ 7],  data, 28  );
        GET_UINT32( X[ 8],  data, 32  );
        GET_UINT32( X[ 9],  data, 36  );
        GET_UINT32( X[ 10], data, 40  );
        GET_UINT32( X[ 11], data, 44  );
        GET_UINT32( X[ 12], data, 48  );
        GET_UINT32( X[ 13], data, 52  );
        GET_UINT32( X[ 14], data, 56  );
        GET_UINT32( X[ 15], data, 60  );

    #define S(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32  - n)))

    #define  P(a,b,c,d,k,s,t)                                \
    {                                                       \
        a += F(b,c,d) + X[k] + t; a = S(a,s) + b;           \
    }

        A = ctx->state[ 0 ];
        B = ctx->state[ 1 ];
        C = ctx->state[ 2 ];
        D = ctx->state[ 3 ];

    #define  F(x,y,z) (z ^ (x & (y ^ z)))

        P( A, B, C, D,  0,  7, 0xD76AA478  );
        P( D, A, B, C,  1, 12, 0xE8C7B756  );
        P( C, D, A, B,  2, 17, 0x242070DB  );
        P( B, C, D, A,  3, 22, 0xC1BDCEEE  );
        P( A, B, C, D,  4,  7, 0xF57C0FAF  );
        P( D, A, B, C,  5, 12, 0x4787C62A  );
        P( C, D, A, B,  6, 17, 0xA8304613  );
        P( B, C, D, A,  7, 22, 0xFD469501  );
        P( A, B, C, D,  8,  7, 0x698098D8  );
        P( D, A, B, C,  9, 12, 0x8B44F7AF  );
        P( C, D, A, B, 10, 17, 0xFFFF5BB1  );
        P( B, C, D, A, 11, 22, 0x895CD7BE  );
        P( A, B, C, D, 12,  7, 0x6B901122  );
        P( D, A, B, C, 13, 12, 0xFD987193  );
        P( C, D, A, B, 14, 17, 0xA679438E  );
        P( B, C, D, A, 15, 22, 0x49B40821  );

    #undef  F

    #define  F(x,y,z) (y ^ (z & (x ^ y)))

        P( A, B, C, D,  1,  5, 0xF61E2562  );
        P( D, A, B, C,  6,  9, 0xC040B340  );
        P( C, D, A, B, 11, 14, 0x265E5A51  );
        P( B, C, D, A,  0, 20, 0xE9B6C7AA  );
        P( A, B, C, D,  5,  5, 0xD62F105D  );
        P( D, A, B, C, 10,  9, 0x02441453  );
        P( C, D, A, B, 15, 14, 0xD8A1E681  );
        P( B, C, D, A,  4, 20, 0xE7D3FBC8  );
        P( A, B, C, D,  9,  5, 0x21E1CDE6  );
        P( D, A, B, C, 14,  9, 0xC33707D6  );
        P( C, D, A, B,  3, 14, 0xF4D50D87  );
        P( B, C, D, A,  8, 20, 0x455A14ED  );
        P( A, B, C, D, 13,  5, 0xA9E3E905  );
        P( D, A, B, C,  2,  9, 0xFCEFA3F8  );
        P( C, D, A, B,  7, 14, 0x676F02D9  );
        P( B, C, D, A, 12, 20, 0x8D2A4C8A  );

    #undef  F
    
    #define  F(x,y,z) (x ^ y ^ z)

        P( A, B, C, D,  5,  4, 0xFFFA3942  );
        P( D, A, B, C,  8, 11, 0x8771F681  );
        P( C, D, A, B, 11, 16, 0x6D9D6122  );
        P( B, C, D, A, 14, 23, 0xFDE5380C  );
        P( A, B, C, D,  1,  4, 0xA4BEEA44  );
        P( D, A, B, C,  4, 11, 0x4BDECFA9  );
        P( C, D, A, B,  7, 16, 0xF6BB4B60  );
        P( B, C, D, A, 10, 23, 0xBEBFBC70  );
        P( A, B, C, D, 13,  4, 0x289B7EC6  );
        P( D, A, B, C,  0, 11, 0xEAA127FA  );
        P( C, D, A, B,  3, 16, 0xD4EF3085  );
        P( B, C, D, A,  6, 23, 0x04881D05  );
        P( A, B, C, D,  9,  4, 0xD9D4D039  );
        P( D, A, B, C, 12, 11, 0xE6DB99E5  );
        P( C, D, A, B, 15, 16, 0x1FA27CF8  );
        P( B, C, D, A,  2, 23, 0xC4AC5665  );

    #undef  F

    #define  F(x,y,z) (y ^ (x | ~z))

        P( A, B, C, D,  0,  6, 0xF4292244  );
        P( D, A, B, C,  7, 10, 0x432AFF97  );
        P( C, D, A, B, 14, 15, 0xAB9423A7  );
        P( B, C, D, A,  5, 21, 0xFC93A039  );
        P( A, B, C, D, 12,  6, 0x655B59C3  );
        P( D, A, B, C,  3, 10, 0x8F0CCC92  );
        P( C, D, A, B, 10, 15, 0xFFEFF47D  );
        P( B, C, D, A,  1, 21, 0x85845DD1  );
        P( A, B, C, D,  8,  6, 0x6FA87E4F  );
        P( D, A, B, C, 15, 10, 0xFE2CE6E0  );
        P( C, D, A, B,  6, 15, 0xA3014314  );
        P( B, C, D, A, 13, 21, 0x4E0811A1  );
        P( A, B, C, D,  4,  6, 0xF7537E82  );
        P( D, A, B, C, 11, 10, 0xBD3AF235  );
        P( C, D, A, B,  2, 15, 0x2AD7D2BB  );
        P( B, C, D, A,  9, 21, 0xEB86D391  );

    #undef  F

        ctx->state[ 0 ] += A;
        ctx->state[ 1 ] += B;
        ctx->state[ 2 ] += C;
        ctx->state[ 3 ] += D;
    }

    void  md5_update( md5_context *ctx, const uint8 *input, uint32 length )
    {
        uint32 left, fill;

        if( ! length ) return ;

        left = ctx->total[ 0] & 0x3F ;
        fill = 64  - left;

        ctx->total[ 0 ] += length;
        ctx->total[ 0] &= 0xFFFFFFFF ;

        if( ctx->total[0 ] < length )
            ctx->total[ 1 ]++;

        if ( left && length >= fill )
        {
            memcpy( ( void  *) (ctx->buffer + left),
                    ( void  *) input, fill );
            md5_process( ctx, ctx->buffer );
            length -= fill;
            input  += fill;
            left = 0 ;
        }

        while( length >= 64  )
        {
            md5_process( ctx, input );
            length -= 64 ;
            input  += 64 ;
        }

        if ( length )
        {
            memcpy( ( void  *) (ctx->buffer + left),
                    ( void  *) input, length );
        }
    }

    static uint8 md5_padding[64 ] =
    {
     0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0
     };

	void md5_finish(md5_context *ctx, md5_result* result)
    {
        uint32 last, padn;
        uint32 high, low;
        uint8 msglen[ 8 ];

        high = ( ctx->total[ 0] >> 29  )
             | ( ctx->total[ 1] <<  3  );
        low  = ( ctx->total[ 0] <<  3  );

        PUT_UINT32( low,  msglen, 0  );
        PUT_UINT32( high, msglen, 4  );

        last = ctx->total[ 0] & 0x3F ;
        padn = ( last < 56 ) ? ( 56 - last ) : ( 120  - last );

        md5_update( ctx, md5_padding, padn );
        md5_update( ctx, msglen, 8  );

        PUT_UINT32( ctx->state[ 0], result->digest,  0  );
        PUT_UINT32( ctx->state[ 1], result->digest,  4  );
        PUT_UINT32( ctx->state[ 2], result->digest,  8  );
        PUT_UINT32( ctx->state[ 3], result->digest, 12  );

		char tmp[4];
		for(int i = 0; i < 16; i++)
		{
#ifdef UTM_WIN
			sprintf_s(tmp, 4, "%02x", result->digest[i]);
#else
			sprintf(tmp, "%02x", result->digest[i]);
#endif
			result->as_string[i*2] = tmp[0];
			result->as_string[i*2 + 1] = tmp[1];
		}
    }

	void md5_string(const char* input, std::string& result)
	{
		md5_context md5c;
		md5_result md5r;

		const unsigned char *p = (const unsigned char*)input;
		size_t len = strlen(input);

		md5_update(&md5c, p, (uint32)len);
		md5_finish(&md5c, &md5r);

		result.assign(md5r.as_string);
	}

	void md5_random(std::string& result)
	{
		int random = utm::get_random(0, 1073741824);
		int random2 = utm::get_random(0, 1073741824);
		char u[40];
		uhex::as_hex((unsigned int)random, u);
		uhex::as_hex((unsigned int)random2, &u[strlen(u)]);
		md5_string(u, result);
	}

#ifdef UTM_DEBUG
	void test_all()
	{
		test_report("md5");

		std::string r1;
		md5_string("Hey Jude! Don't make it bad.", r1);
		TEST_CASE_CHECK(r1, std::string("f29e5a0af737ee60be064e4f056c0e11"));

		std::string n1, n2;
		md5_random(n1);
		md5_random(n2);
		TEST_CASE_NOTCHECK(n1, n2);

		return;
	}
#endif
}

}
