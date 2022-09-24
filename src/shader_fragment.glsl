#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Cor HUD
in vec4 cor_interpolada_pelo_rasterizador;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define EARTH 0
#define PLANAR 1
#define PLANE 2
#define HUD 3
#define CUBEMAP 4
#define ASTEROID 5
#define TESTCUBE 6
uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D earth_day;
uniform sampler2D earth_night;
uniform sampler2D earth_clouds;

uniform sampler2D skybox;

uniform sampler2D asteroid;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    if ( object_id == EARTH || object_id == ASTEROID)
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        
        vec4 p_prime = bbox_center + (position_model - bbox_center) / length(position_model - bbox_center);
        vec4 p_vec = p_prime - bbox_center;

        float theta = atan(p_vec.x, p_vec.z);
        float phi = asin(p_vec.y);

        U = (theta + M_PI) / (2*M_PI);
        V = (phi + M_PI_2) / M_PI;
    }
    else if ( object_id == PLANAR )
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        U = (position_model.x - minx) / (maxx - minx);
        V = (position_model.y - miny) / (maxy - miny);
    }
    else if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
    }
    
    if (object_id == HUD)
    {
        color = vec4(1.0, 1.0, 1.0, 1.0); 
    }
    else if (object_id == CUBEMAP)
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        
        vec4 p_prime = bbox_center + (position_model - bbox_center) / length(position_model - bbox_center);
        vec4 p_vec = p_prime - bbox_center;

        float theta = atan(p_vec.x, p_vec.z);
        float phi = asin(p_vec.y);

        U = (theta + M_PI) / (2*M_PI);
        V = (phi + M_PI_2) / M_PI;

        color = texture(skybox, vec2(U, V));
    }
    else
    {
        vec3 Kd0;
        float lambert;
        if (object_id == EARTH)
        {
            vec3 Kd0 = texture(earth_day, vec2(U,V)).rgb;
            
            // Equação de Iluminação
            float lambert = max(0,dot(n,l));
            float intensity_night_lights = 100.0;

            if (lambert == 0)
                Kd0 += intensity_night_lights*texture(earth_night, vec2(U,V)).rgb;

            float instensity_clouds = 5.0;
            Kd0 += instensity_clouds*texture(earth_clouds, vec2(U,V)).rgb; // adiciona nuvens

            color.rgb = Kd0 * (lambert + 0.01);
            color.a = 1;
        }
        else if (object_id == ASTEROID)
        {
            vec3 Kd0 = texture(asteroid, vec2(U,V)).rgb;

            // Equação de Iluminação
            float lambert = max(0,dot(n,l));

            color.rgb = Kd0 * (lambert + 0.01);
            color.a = 1;
        }
        else if (object_id == TESTCUBE)
        {
            vec3 Kd0 = vec3(1.0, 1.0, 1.0);

            // Equação de Iluminação
            float lambert = max(0,dot(n,l));

            color.rgb = Kd0 * (lambert + 0.01);
            color.a = 1;
        }
    }

    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
} 