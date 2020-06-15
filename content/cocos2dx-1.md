Title: cocos2dx-4.0-游戏引擎(1)
Date: 2020-06-06 06:04
Category: cocos2dx
Tags: c++, cocos2dx
Slug: cocos2dx-1
Authors: Xuan Mingyi

### 名词解释


英文 | 中文 | 解释
:-: | :-: | :-:
[Sprite](http://en.wikipedia.org/wiki/Sprite_(computer_graphics)) | 精灵 | 精灵是一个渲染组件
SpriteFrame | 精灵帧 | -
Texture | 纹理 | -
TextureCache | 纹理缓存 | -
SpriteFrameCache | 精灵帧缓存 | -
Animation | 动画 | 动画信息
AnimationCache | 动画缓存 | -
Animate | 动画执行体 | 包含动画的执行信息

### Texture & TextureCache

`Texture`纹理就是我们普通理解的纹理贴图,就是一张图片。
`TextureCache`就是纹理缓存

获得纹理缓存,在cocos2dx 4.x以上，我们通过Director

```c++
Director::getInstance()->getTextureCache();
cout << Director::getInstance()->getTextureCache()->getCachedTextureInfo() << endl; // 打印出纹理的缓存信息
```

从纹理的缓存信息中，我们能看到不同缓存的id，图片位置已经大小等信息。


### SpriteFrame & SpriteFrameCache

`SpriteFrame`是一帧的意思，他由Texture和一个Rect组成。
`SpriteFrameCache`是一个包含Map的Cache，简单的Key-Value系统

*SpriteFrame*创建方法:

```c++
static SpriteFrame* create(const std::string& filename, const Rect& rect);
static SpriteFrame* create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect);
static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
```

*SpriteFrameCache* 添加方法:
```c++
void addSpriteFramesWithFile(const std::string& plist);
void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);
void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);
void addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture);
void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);
void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture, const std::string &plist);
void addSpriteFramesWithDictionary(ValueMap& dictionary, const std::string &texturePath, const std::string &plist);
```

### Sprite

`Sprite`是精灵，是一个渲染的组件，和他同级别的是`Label`、`Rich Text`, addChild加入的就是这个，这些类都派生自`Node`


创建方法:

```c++
static Sprite* create();
static Sprite* create(const std::string& filename);
static Sprite* create(const PolygonInfo& info);
static Sprite* create(const std::string& filename, const Rect& rect);
static Sprite* createWithTexture(Texture2D *texture);
static Sprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false);
static Sprite* createWithSpriteFrame(SpriteFrame *spriteFrame);
static Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);
```

`Sprite`包含一个`SpriteFrame`的属性,我们可以通过下面的方法

```c++
sprite->setSpriteFrame(newFrame); // 这个方法替换
```


### Animation

`Animation`从`Vector<SpriteFrame*>`创建一个动画，里面包含每一帧的数据，每一帧之间的间隔等。

创建方法:

```c++
static Animation* create();
static Animation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
static Animation* create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops = 1);
```

### Animate

`Animate`是执行的一个类，是执行相关的信息，包括下一帧，已经循环了几次等等信息。

创建方法:

```c++
static Animate* create(Animation *animation);
```

