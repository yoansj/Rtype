/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** IEncoder
*/

#ifndef IENCODER_HPP_
#define IENCODER_HPP_

#include <vector>

namespace Babel {
    namespace Codec {
        class IEncoder {
            public:
                virtual ~IEncoder() = default;

                /*
                ** Check for errors and throw a custom error
                */
                virtual void checkError() const = 0;

                /*
                ** Encode a pointer-to-float stored in a vector
                ** @param pcm pointer-to-float stored in a vector
                ** @return pointer-to-uchar stored in a vector which represents the encoded data
                */
                virtual std::vector<unsigned char> encode(std::vector<float> const &pcm) = 0;

                /*
                ** Encode a list of pointer-to-float stored in vector.
                ** The function will iterates on each element of the vector and execute *encode* function on it.
                ** It stores the result of each iteration in a new vector and returns it
                ** @param pcm vector of pointer-to-float stored in a vector
                ** @return vector of pointer-to-uchar stored in a vector which represents the encoded data
                */
                virtual std::vector<std::vector<unsigned char>> encodeList(std::vector<std::vector<float>> const &pcm) = 0;

                /*
                ** Operator overload to *encode* function
                ** @param pcm pointer-to-float stored in a vector
                ** @return pointer-to-uchar stored in a vector which represents the encoded data
                */
                virtual std::vector<unsigned char> operator()(std::vector<float> const &) = 0;

                /*
                ** Operator overload to *encodeList* function
                ** @param pcm vector of pointer-to-float stored in a vector
                ** @return vector of pointer-to-uchar stored in a vector which represents the encoded data
                */
                virtual std::vector<std::vector<unsigned char>> operator()(std::vector<std::vector<float>> const &) = 0;
        };
    }
}

#endif /* !IENCODER_HPP_ */
