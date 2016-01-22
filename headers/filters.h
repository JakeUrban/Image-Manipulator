#ifndef FILTERS_H
#define FILTERS_H
#include <source.h>
#include <sink.h>
#include <filter.h>
#include <stdio.h>

class LRConcat : public Filter
{
	public:
		LRConcat(void);
		~LRConcat(void);
		void Execute(void);
		const char* FilterName() {return name;}
	private:
		const char* name;
};

class Shrinker : public Filter
{
	public:
		Shrinker(void);
		~Shrinker(void);
		void Execute(void);
		const char* FilterName() {return name;}
	private:
		const char* name;
};


class TBConcat : public Filter
{
	public:
		TBConcat(void);
		~TBConcat(void);
		void Execute(void);
		const char* FilterName() {return name;}
	private:
		const char* name;
};

class Blender : public Filter
{
	public:
		Blender();
		~Blender();
		void Execute(void);
		void SetFactor(float f) {factor = f;}
		const char* FilterName() {return name;}
	protected:
		float factor;
	private:
		const char* name;
};


class Crop : public Filter
{
  public:
                   Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName() { return "Crop"; };
    virtual void   Execute();
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }

  private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose : public Filter
{
	public:
		Transpose();
		~Transpose();
		virtual void Execute(void);
		const char* FilterName(void) {return name;}
	private:
		const char* name;
};

class Invert : public Filter
{
	public:
		Invert();
		~Invert();
		virtual void Execute(void);
		const char* FilterName(void) {return name;}
	private:
		const char* name;
};

class Checkerboard : public Filter
{
	public:
		Checkerboard();
		~Checkerboard();
		virtual void Execute(void);
		const char* FilterName(void) {return name;}
	private:
		const char* name;
};

class Color : public Source
{
	public:
		Color(int w,int h, unsigned char red, unsigned char green, unsigned char blue);
		const char* SourceName(void) {return name;}
		void Execute(void);
	private:
		const char* name;
		unsigned char r, g, b;
};

class CheckSum : public Sink
{
	public:
		CheckSum(void);
		const char* SinkName(void) {return name;}
		void OutputCheckSum(const char*);
	private:
		const char* name;
		unsigned int r,g,b;
		FILE* file;
};
#endif
