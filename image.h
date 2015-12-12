#ifndef IMAGE_H
#define IMAGE_H

class Source;

class Image
{
	private:
	int height, width;
	unsigned char *data;
	Source *source;

	public:
		Image(void);
		Image(int h, int w, unsigned char *d);
		Image(Image &);
	void Update(void) const;
	void SetSource(Source* src);
	int GetHeight(void) const;
	int GetWidth(void) const;
	const unsigned char* GetData(void) const;
	unsigned char* SetData(void) const;
	void ResetSize(int h, int w);
};

#endif

