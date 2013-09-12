#ifndef DOUFEI_MULTIBITMAP_HEADER
#define DOUFEI_MULTIBITMAP_HEADER
#include <memory>
#define  BITS_ONE_INT 32
#define  SHIFT 5
#define  MASK 0x1F
class CMultiBitMap
{
public:
	CMultiBitMap(const size_t size = 0) ;
	~CMultiBitMap() ;

	inline bool setBit(size_t i, bool bitValue) ;//设置第i位是bitValue,true表示1，false表示0
	inline bool getBit(size_t i) ; //判断第i位是否是1
	inline void setAll(bool bitValue) ; //设置所有的bit是1或0
	inline size_t oneCount() ; //统计1的个数

	void resize(size_t newSize) ; //重新分配大小，原来的空间都被删除，并且原来的数据并清除


private:
	int *bits ; //存储所有的bits
	size_t bitSize ; //bit位的个数
};

inline bool CMultiBitMap :: setBit(size_t i, bool bitValue)
{
	if (i >= bitSize) return false ; //设置失败，超出范围
	if (bitValue)
		bits[i >> SHIFT] |= (1 << (i & MASK)) ;
	else
		bits[i >> SHIFT] &= ~(1 << (i & MASK)) ;
	return true ;
}

inline bool CMultiBitMap :: getBit(size_t i)
{
	 if (bits[i >> SHIFT] & (1 << (i & MASK)) )
		 return true ;
	 else
		  return false ;
}

inline void CMultiBitMap :: setAll(bool bitValue) 
{

	size_t intCount = bitSize >> SHIFT ;
	if (bitSize & MASK)
		intCount ++ ;

	if (bitValue)
		memset(bits, 0xFF, sizeof(int) * intCount) ;
	else
		memset(bits, 0x00, sizeof(int) * intCount) ;
}

inline size_t CMultiBitMap :: oneCount()
{
	size_t ret = 0 ;
	for (size_t i = 0; i < bitSize; ++ i)
		if (getBit(i)) ++ret;
	return ret ;
}
#endif