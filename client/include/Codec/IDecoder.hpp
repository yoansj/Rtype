/*
** EPITECH PROJECT, 2020
** b-cpp-500-par-5-1-babel-aurele.auboin
** File description:
** IDecoder
*/

#ifndef IDECODER_HPP_
#define IDECODER_HPP_

#include <vector>

namespace Babel {
    namespace Codec {
        class IDecoder {
            public:
                virtual ~IDecoder() = default;

                /*
                ** Check for errors and throw a custom error
                */
                virtual void checkError() const = 0;

                /*
                ** Decode a packet which is pointer-to-uchar stored in a vector
                ** @param pcm pointer-to-uchar stored in a vector
                ** @return pointer-to-float stored in a vector which represents the decoded data
                */
                virtual std::vector<float> decode(std::vector<unsigned char> const &packet) = 0;

                /*
                ** Decode a list of pointer-to-uchar stored in vector.
                ** The function will iterates on each element of the vector and execute *decode* function on it.
                ** It stores the result of each iteration in a new vector and returns it
                ** @param pcm vector of pointer-to-uchar stored in a vector
                ** @return vector of pointer-to-float stored in a vector which represents the decoded data
                */
                virtual std::vector<std::vector<float>> decodeList(std::vector<std::vector<unsigned char>> const &packets) = 0;

                /*
                ** Operator overload to *decode* function
                ** @param pcm pointer-to-uchar stored in a vector
                ** @return pointer-to-float stored in a vector which represents the decoded data
                */
                virtual std::vector<float> operator()(std::vector<unsigned char> const &) = 0;

                /*
                ** Operator overload to *decodeList* function
                ** @param pcm vector of pointer-to-uchar stored in a vector
                ** @return vector of pointer-to-float stored in a vector which represents the decoded data
                */
                virtual std::vector<std::vector<float>> operator()(std::vector<std::vector<unsigned char>> const &) = 0;
        };
    }
}
#endif /* !IDECODER_HPP_ */
