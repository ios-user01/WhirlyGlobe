/*
 *  DynamicTextureAtlas.h
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 2/28/13.
 *  Copyright 2011-2013 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import <vector>
#import <set>
<<<<<<< HEAD
=======
#import <UIKit/UIKit.h>
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b

#import "Identifiable.h"
#import "WhirlyVector.h"
#import "Texture.h"
#import "TextureAtlas.h"

namespace WhirlyKit
{

/** The dynamic texture can have pieces of itself replaced in the layer thread while
    being used in the renderer.  It's used to implement dynamic texture atlases.
  */
class DynamicTexture : public TextureBase
{
public:
    /// Constructor for sorting
    DynamicTexture(SimpleIdentity myId) : TextureBase(myId), layoutGrid(NULL) { }
    /// Construct with a name, square texture size, cell size (in texels), and the memory format
    DynamicTexture(const std::string &name,int texSize,int cellSize,GLenum format);
    ~DynamicTexture();
    
    /// Represents a region in the texture
    class Region
    {
    public:
        int sx,sy,ex,ey;
    };
    
    /// Create an appropriately empty texture in OpenGL ES
    bool createInGL(OpenGLMemManager *memManager);
    
    /// Render side only.  Don't call this.  Destroy the OpenGL ES version
    void destroyInGL(OpenGLMemManager *memManager);
    
    /// Add the given texture at the given location.
    /// This is probably called on the layer thread
    void addTexture(Texture *tex,const Region &region);
    
    /// Add the data at a given location in the texture
<<<<<<< HEAD
    void addTextureData(int startX,int startY,int width,int height,RawDataRef data);
=======
    void addTextureData(int startX,int startY,int width,int height,NSData *data);
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b
    
    /// Set or clear a given region
    void setRegion(const Region &region,bool enable);
    
    /// Look for an open region of the given cell extents
    bool findRegion(int cellsX,int cellsY,Region &region);
    
    /// Add a region to the list of ones to be cleared.
    /// This is called by the renderer
    void addRegionToClear(const Region &region);
    
    /// Return true if this isn't representing any regions
    bool empty();
    
    /// Number of sub textures we're currently representing
    int &getNumRegions() { return numRegions; }
    
    /// Return texture cell utilization
    void getUtilization(int &numCell,int &usedCell);
    
protected:
    /// Used for debugging
    std::string name;
    
    /// If set, this is a compressed format (assume PVRTC4)
    bool compressed;
    /// Texture memory format
    GLenum format,type;
    /// Number of texels on a side
    int texSize;
    /// Number of texels in a cell
    int cellSize;
    /// Number of cells on a side
    int numCell;
    
    // Use to track where sub textures are
    bool *layoutGrid;
    
    pthread_mutex_t regionLock;
    /// These regions have been released by the renderer
    std::vector<Region> releasedRegions;
    
    /// Number of active regions (as far as the texture is concerned)
    int numRegions;
};

typedef std::vector<DynamicTexture *> DynamicTextureVec;

// Used to sort dynamic texture vectors
typedef struct
{
    bool operator () (const DynamicTextureVec *a,const DynamicTextureVec *b) { return a->at(0)->getId() < b->at(0)->getId(); }
} DynamicTextureVecSorter;

/// Copy data into a dynamic texture (on the main thread)
class DynamicTextureAddRegion : public ChangeRequest
{
public:
<<<<<<< HEAD
    DynamicTextureAddRegion(SimpleIdentity texId,int startX,int startY,int width,int height,RawDataRef data)
    : texId(texId), startX(startX), startY(startY), width(width), height(height), data(data) { }
    

    /// Add the region.  Never call this.
	void execute(Scene *scene,WhirlyKit::SceneRendererES *renderer,WhirlyKit::View *view);
=======
    DynamicTextureAddRegion(SimpleIdentity texId,int startX,int startY,int width,int height,NSData *data)
    : texId(texId), startX(startX), startY(startY), width(width), height(height), data(data) { }

    /// Add the region.  Never call this.
	void execute(Scene *scene,WhirlyKitSceneRendererES *renderer,WhirlyKitView *view);
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b
    
protected:
    SimpleIdentity texId;
    int startX,startY,width,height;
<<<<<<< HEAD
    RawDataRef data;
=======
    NSData *data;
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b
};
    
/// Tell a dynamic texture that a region has been released for use
class DynamicTextureClearRegion : public ChangeRequest
{
public:
    /// Construct with the dynamic texture ID and the region to clear
    DynamicTextureClearRegion(SimpleIdentity texId,const DynamicTexture::Region &region) : texId(texId), region(region) { }

    /// Clear the region from the given dynamic texture.  Never call this.
<<<<<<< HEAD
	void execute(Scene *scene,WhirlyKit::SceneRendererES *renderer,WhirlyKit::View *view);
=======
	void execute(Scene *scene,WhirlyKitSceneRendererES *renderer,WhirlyKitView *view);
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b

protected:
    SimpleIdentity texId;
    DynamicTexture::Region region;
};

/** The dynamic texture atlas manages a variable number of dynamic textures into which it will stuff
    individual textures.  You use it by adding your individual Textures and passing the
    change requests on to the layer thread (or Scene).  You can also clear your Textures later
    by region.
  */
class DynamicTextureAtlas
{
public:
    /// Construct with the square size of the textures, the cell size (in pixels) and the pixel format
<<<<<<< HEAD
    DynamicTextureAtlas(int texSize,int cellSize,GLenum format,int imageDepth=1,bool mainThreadMerge=false);
    ~DynamicTextureAtlas();

    /// Fudge factor for border pixels.  We'll add this/pixelSize to the lower left
    ///  and subtract this/pixelSize from the upper right for each texture application.
    void setPixelFudgeFactor(float pixFudge);

=======
    DynamicTextureAtlas(int texSize,int cellSize,GLenum format,int imageDepth=1);
    ~DynamicTextureAtlas();

>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b
    /// Try to add the texture to one of our dynamic textures, or create one.
    bool addTexture(const std::vector<Texture *> &textures,Point2f *realSize,Point2f *realOffset,SubTexture &subTex,OpenGLMemManager *memManager,ChangeSet &changes,int borderPixels,int bufferPixels=0);
    
    /// Free up the space for a texture from one of the dynamic textures
    void removeTexture(const SubTexture &subTex,ChangeSet &changes);
    
    /// Return the IDs for the dynamic textures we're using
    void getTextureIDs(std::vector<SimpleIdentity> &texIDs,int which);

<<<<<<< HEAD
    /// Look for any textures that should be cleaned up
    void cleanup(ChangeSet &changes);

=======
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b
    /// Clear out the active dynamic textures.  Caller deals with the
    ///  change requests.
    void shutdown(ChangeSet &changes);
    
        /// Print out some utilization info
    void log();

protected:
    /// This maps a given texture to its location in a dynamic texture
    class TextureRegion
    {
    public:
        bool operator < (const TextureRegion &that) const { return subTex.getId() < that.subTex.getId(); }
        
        SubTexture subTex;
        SimpleIdentity dynTexId;
        DynamicTexture::Region region;
    };

    int imageDepth;
    int texSize;
    int cellSize;
    GLenum format;
<<<<<<< HEAD
    float pixelFudge;
    bool mainThreadMerge;

=======
    
>>>>>>> 8b82d413fa1eea92c764cf2cc76045872be7384b
    typedef std::set<TextureRegion> TextureRegionSet;
    TextureRegionSet regions;
    typedef std::set<DynamicTextureVec *,DynamicTextureVecSorter> DynamicTextureSet;
    DynamicTextureSet textures;
};

}
