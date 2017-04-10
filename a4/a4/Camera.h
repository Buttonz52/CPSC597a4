#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#define M_PI 3.1415926535897932384626
#define M_PI_4 M_PI / 4

using namespace glm;
using namespace std;

class Camera
{
private:
	float azu;
	float alt;
	float radius;
  
	float fov;
	float _near;
	float _far;

  float asp;
	
	vec3 center;
public:
	Camera();
	Camera(vec3 &center);
	Camera(vec3 &center, vec3 &focalPoint);
	~Camera();

	void setCenter(vec3 &);

	void setAzu(float);
	void setAlt(float);
	void setRadius(float);
  
	void incrementAzu(float);
	void incrementAlt(float);
	void incrementRadius(float);
	 
    void setAsp(float);
 
	vec3 focalPoint;
	mat4 calculateProjectionMatrix();
	mat4 calculateViewMatrix();

	void translate3D(vec3);
	vec3 *getCenter();
	void setInitValues();
};