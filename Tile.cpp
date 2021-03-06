#include <stdio.h>


// TODO: reference additional headers your program requires here
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>

#include "Chunk.h"


Tile::Tile(int id_t, int l){
    id_temp = id_t;
    layer = l;
}


Tile::~Tile()
{
	
}


void Tile::Reload(std::string new_id)
{
	id = new_id;
	if(new_id == "0"){
		reach_sun = false;
		weight = 0;
		max_tension = 0;
		rigid = false;
		reach_floor = false;
	}
	else if(new_id == "D"){
        reach_sun = false;
		weight = 20;
		max_tension = 100;
		rigid = false;
		reach_floor = true;
	}
	else if(new_id == "d"){
        reach_sun = false;
		weight = 20;
		max_tension = 100;
		rigid = false;
		reach_floor = false;
	}
	else if(new_id == "r"){
        reach_sun = false;
		weight = 10;
		max_tension = 200;
		rigid = false;
		reach_floor = false;
	}
    else if(new_id == "C"){
        reach_sun = false;
        weight = 20;
        max_tension = 500;
        rigid = false;
        reach_floor = false;
    }
    else if(new_id == "c"){
        reach_sun = false;
        weight = 20;
        max_tension = 500;
        rigid = false;
        reach_floor = false;
    }
	else{
		Reload("0");
	}

	
}
bool Tile::drawable(){
    if(!reach_sun) return false;
	bool res =false;
    if(layer==1 && id=="0") return true;
	for(int i=0; i<8; i++){
		if(neighbors[i] !=nullptr && neighbors[i]->id=="0"){
			res=true;
			break;
		}
	}
	return res;
}
void Tile::DrawFadeOut(sf::RenderWindow & renderWindow, TextureManager &t, sf::VertexArray &vertexArray){
    if(neighbors[0] != nullptr && neighbors[0]->neighbors[8]->id != "0" && !neighbors[0]->drawable()  && neighbors[7]->drawable() && neighbors[1]->drawable()){
        appendSpriteToArray(t, vertexArray, -1, "S2", 90);
    }
    if(neighbors[1] != nullptr && neighbors[1]->neighbors[8]->id != "0" && !neighbors[1]->drawable() ){
        appendSpriteToArray(t, vertexArray, -1, "S", 180);
    }
    if(neighbors[2] != nullptr && neighbors[2]->neighbors[8]->id != "0" && !neighbors[2]->drawable() && neighbors[3]->drawable() && neighbors[1]->drawable()){
        appendSpriteToArray(t, vertexArray, -1, "S2", 180);

    }
    if(neighbors[3] != nullptr && neighbors[3]->neighbors[8]->id != "0" && !neighbors[3]->drawable()){
        appendSpriteToArray(t, vertexArray, -1, "S", -90);
    }
    if(neighbors[4] != nullptr && neighbors[4]->neighbors[8]->id != "0" && !neighbors[4]->drawable() && neighbors[3]->drawable() && neighbors[5]->drawable()){
        appendSpriteToArray(t, vertexArray, -1, "S2", -90);
    }
    if(neighbors[5] != nullptr && neighbors[5]->neighbors[8]->id != "0" && !neighbors[5]->drawable()){
        appendSpriteToArray(t, vertexArray, -1, "S", 0);

    }
    if(neighbors[6] != nullptr && neighbors[6]->neighbors[8]->id != "0" && !neighbors[6]->drawable() && neighbors[5]->drawable() && neighbors[7]->drawable() ){
        appendSpriteToArray(t, vertexArray, -1, "S2", 0);

    }
    if(neighbors[7] != nullptr && (neighbors[7]->neighbors[8]->id != "0") && !neighbors[7]->drawable() ){
        appendSpriteToArray(t, vertexArray, -1, "S", 90);
    }
}
void Tile::DrawAmbientOclusion(sf::RenderWindow & renderWindow, TextureManager &t, sf::VertexArray &vertexArray){
    if(neighbors[0] != nullptr && !neighbors[0]->drawable() && neighbors[7]->drawable() && neighbors[1]->drawable()){

    }
    if(neighbors[1] != nullptr && neighbors[1]->neighbors[8]->id!="0"){
        appendSpriteToArray(t, vertexArray, -1, "s", 180);
    }
    if(neighbors[2] != nullptr && !neighbors[2]->drawable() && neighbors[3]->drawable() && neighbors[1]->drawable()){

    }
    if(neighbors[3] != nullptr && neighbors[3]->neighbors[8]->id!="0"){
        appendSpriteToArray(t, vertexArray, -1, "s", -90);
    }
    if(neighbors[4] != nullptr && !neighbors[4]->drawable() && neighbors[3]->drawable() && neighbors[5]->drawable()){

    }
    if(neighbors[5] != nullptr && neighbors[5]->neighbors[8]->id!="0"){
        appendSpriteToArray(t, vertexArray, -1, "s", 0);
    }
    if(neighbors[6] != nullptr && !neighbors[6]->drawable() && neighbors[5]->drawable() && neighbors[7]->drawable()){

    }
    if(neighbors[7] != nullptr && neighbors[7]->neighbors[8]->id!="0"){
        appendSpriteToArray(t, vertexArray, -1, "s", 90);
    }
}
void Tile::DrawOuts(sf::RenderWindow & renderWindow, TextureManager &t, sf::VertexArray &vertexArray)
{
    Tile* t1 = neighbors[1];
    Tile* t3 = neighbors[3];
    Tile* t5 = neighbors[5];
    Tile* t7 = neighbors[7];
    bool valid_t1= (t1 != nullptr && (t1->id =="d" || t1->id =="D" || t1->id =="c" || t1->id =="C"));
    bool valid_t3= (t3 != nullptr && (t3->id =="d" || t3->id =="D" || t3->id =="c" || t3->id =="C"));
    bool valid_t5= (t5 != nullptr && (t5->id =="d" || t5->id =="D" || t5->id =="c" || t5->id =="C"));
    bool valid_t7 = (t7 != nullptr && (t7->id =="d" || t7->id =="D" || t7->id =="c" || t7->id =="C"));
    if(valid_t1 && valid_t3 && t1->id==t3->id){
        std::string id_mini = t1->id;
        id_mini.append("_out");
        appendSpriteToArray(t, vertexArray, 1, id_mini, 0);
    }
    if(valid_t1 && valid_t7 && t1->id==t7->id){
        std::string id_mini = t1->id;
        id_mini.append("_out");
        appendSpriteToArray(t, vertexArray, 0, id_mini, 0);
    }
    if(valid_t3 && valid_t5 && t3->id==t5->id){
        std::string id_mini = t3->id;
        id_mini.append("_out");
        appendSpriteToArray(t, vertexArray, 3, id_mini, 0);
    }
    if(valid_t7 && valid_t5 && t5->id==t7->id){
        std::string id_mini = t5->id;
        id_mini.append("_out");
        appendSpriteToArray(t, vertexArray, 2, id_mini, 0);
    }
}
void Tile::appendSpriteToArray(TextureManager &t, sf::VertexArray &vertexArray, int mini_pos, std::string id_in_tex,int rotation){
    float increment_x=0;
    float increment_y=0;
    float increment_x_tex=0;
    float increment_y_tex=0;
    int divisor=2;
    if(mini_pos==1) {
        increment_x+=Chunk::TILE_SIZE/2;
        increment_x_tex+=t.size_sprite.x/2;
    }
    else if(mini_pos==2) {
        increment_y+=Chunk::TILE_SIZE/2;
        increment_y_tex+=t.size_sprite.y/2;
    }
    else if(mini_pos==3){
        increment_x+=Chunk::TILE_SIZE/2;
        increment_y+=Chunk::TILE_SIZE/2;
        increment_y_tex+=t.size_sprite.y/2;
        increment_x_tex+=t.size_sprite.x/2;
    }
    if(mini_pos==-1) divisor=1;
    sf::Vector2i position_sprite = t.getPositionSprite(id_in_tex);
    sf::Vector2f pos_tex1, pos_tex2, pos_tex3, pos_tex4;
    if(rotation==0){
        pos_tex1 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex2 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex3 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
        pos_tex4 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
    } else if(rotation==90){
        pos_tex2 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex3 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex4 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
        pos_tex1 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
    }
    else if(rotation==-90){
        pos_tex4 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex1 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex2 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
        pos_tex3 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
    }
    else if(rotation==180){
        pos_tex3 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex4 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+increment_y_tex);
        pos_tex1 = sf::Vector2f(position_sprite.x+t.size_sprite.x/divisor+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
        pos_tex2 = sf::Vector2f(position_sprite.x+increment_x_tex, position_sprite.y+t.size_sprite.y/divisor+increment_y_tex);
    }


    vertexArray.append(sf::Vertex(sf::Vector2f(position.x+increment_x,position.y+increment_y), pos_tex1));
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x+increment_x+Chunk::TILE_SIZE/divisor,position.y+increment_y), pos_tex2));
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x+increment_x+Chunk::TILE_SIZE/divisor,position.y+increment_y+Chunk::TILE_SIZE/divisor), pos_tex3));
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x+increment_x,position.y+Chunk::TILE_SIZE/divisor+increment_y), pos_tex4));
}
void Tile::DrawIns(sf::RenderWindow & renderWindow, TextureManager &t, sf::Shader &tile_shader, sf::VertexArray &vertexArray){
    bool is_mini[4] ={0,0,0,0};
    if(neighbors[1] != nullptr && neighbors[1]->id=="0" && neighbors[2] != nullptr && neighbors[2]->id=="0" && neighbors[3] != nullptr && neighbors[3]->id=="0"){
        std::string id_mini = id;
        id_mini.append("_in");
        is_mini[0]=true;
        appendSpriteToArray(t, vertexArray, 1, id_mini, 0);
    }
    if(neighbors[3] != nullptr && neighbors[3]->id=="0" && neighbors[4] != nullptr && neighbors[4]->id=="0" && neighbors[5] != nullptr && neighbors[5]->id=="0"){
        std::string id_mini = id;
        id_mini.append("_in");
        is_mini[1]=true;
        appendSpriteToArray(t, vertexArray, 3, id_mini, 0);
    }
    if(neighbors[5] != nullptr && neighbors[5]->id=="0" && neighbors[6] != nullptr && neighbors[6]->id=="0" && neighbors[7] != nullptr && neighbors[7]->id=="0"){
        std::string id_mini = id;
        id_mini.append("_in");
        is_mini[2]=true;
        appendSpriteToArray(t, vertexArray, 2, id_mini, 0);
    }
    if(neighbors[7] != nullptr && neighbors[7]->id=="0" && neighbors[1] != nullptr && neighbors[1]->id=="0" && neighbors[0] != nullptr && neighbors[0]->id=="0"){
        std::string id_mini = id;
        id_mini.append("_in");
        is_mini[3]=true;
        appendSpriteToArray(t, vertexArray, 0, id_mini, 0);
    }
    if(!is_mini[0] && !is_mini[1] && !is_mini[2] && !is_mini[3]){
        appendSpriteToArray(t, vertexArray, -1, id, 0);
    } else{
        if(!is_mini[0]) appendSpriteToArray(t, vertexArray, 1, id, 0);
        if(!is_mini[1]) appendSpriteToArray(t, vertexArray, 3, id, 0);
        if(!is_mini[2]) appendSpriteToArray(t, vertexArray, 2, id, 0);
        if(!is_mini[3]) appendSpriteToArray(t, vertexArray, 0, id, 0);
    }
}

void Tile::DrawGrass(sf::RenderWindow & renderWindow, TextureManager &t, sf::VertexArray &vertexArray){
    sf::Vector2f pos_tex1, pos_tex2, pos_tex3, pos_tex4;
    sf::Vector2i position_sprite = t.getPositionSprite("grass0");
    pos_tex1 = sf::Vector2f(position_sprite.x, position_sprite.y);
    pos_tex2 = sf::Vector2f(position_sprite.x+t.size_sprite.x, position_sprite.y);
    pos_tex3 = sf::Vector2f(position_sprite.x+t.size_sprite.x, position_sprite.y+t.size_sprite.y);
    pos_tex4 = sf::Vector2f(position_sprite.x, position_sprite.y+t.size_sprite.y);
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x,position.y-GetHeight()/2), pos_tex1));
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x+Chunk::TILE_SIZE,position.y-GetHeight()/2), pos_tex2));
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x+Chunk::TILE_SIZE,position.y-GetHeight()/2+Chunk::TILE_SIZE), pos_tex3));
    vertexArray.append(sf::Vertex(sf::Vector2f(position.x,position.y+Chunk::TILE_SIZE-GetHeight()/2),
                                  pos_tex4));
    if(neighbors[3]!=nullptr && (neighbors[3]->id !="D" || (neighbors[2] !=nullptr && neighbors[2]->neighbors[8]->id !="0"))){
        sf::Vector2i position_sprite = t.getPositionSprite("grass1");
        pos_tex1 = sf::Vector2f(position_sprite.x, position_sprite.y);
        pos_tex2 = sf::Vector2f(position_sprite.x+t.size_sprite.x, position_sprite.y);
        pos_tex3 = sf::Vector2f(position_sprite.x+t.size_sprite.x, position_sprite.y+t.size_sprite.y);
        pos_tex4 = sf::Vector2f(position_sprite.x, position_sprite.y+t.size_sprite.y);
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x+GetWidth(),position.y-GetHeight()/2), pos_tex1));
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x+GetWidth()+Chunk::TILE_SIZE,position.y-GetHeight()/2), pos_tex2));
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x+GetWidth()+Chunk::TILE_SIZE,position.y-GetHeight()/2+Chunk::TILE_SIZE), pos_tex3));
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x+GetWidth(),position.y+Chunk::TILE_SIZE-GetHeight()/2), pos_tex4));
    }
    if(neighbors[7]!=nullptr && (neighbors[7]->id !="D"|| (neighbors[0] !=nullptr && neighbors[0]->neighbors[8]->id !="0"))){
        sf::Vector2i position_sprite = t.getPositionSprite("grass1");
        pos_tex3 = sf::Vector2f(position_sprite.x, position_sprite.y);
        pos_tex4 = sf::Vector2f(position_sprite.x+t.size_sprite.x, position_sprite.y);
        pos_tex1 = sf::Vector2f(position_sprite.x+t.size_sprite.x, position_sprite.y+t.size_sprite.y);
        pos_tex2 = sf::Vector2f(position_sprite.x, position_sprite.y+t.size_sprite.y);
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x-GetWidth(),position.y-GetHeight()/2+5), pos_tex1));
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x-GetWidth()+Chunk::TILE_SIZE,position.y-GetHeight()/2+5), pos_tex2));
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x-GetWidth()+Chunk::TILE_SIZE,position.y-GetHeight()/2+5+Chunk::TILE_SIZE), pos_tex3));
        vertexArray.append(sf::Vertex(sf::Vector2f(position.x-GetWidth(),position.y+Chunk::TILE_SIZE-GetHeight()/2+5), pos_tex4));
    }
}
void Tile::Draw(sf::RenderWindow & renderWindow, TextureManager &t, sf::Shader &tile_shader, sf::VertexArray &vertexArray)
{

    if(reach_sun) {
        if (layer == 1) {
                if (neighbors[8] != nullptr && neighbors[8]->id != "0") neighbors[8]->Draw(renderWindow, t, tile_shader,vertexArray);
                DrawIns(renderWindow, t, tile_shader,vertexArray);
                DrawFadeOut(renderWindow, t,vertexArray);




        }
        else {
            DrawIns(renderWindow, t, tile_shader,vertexArray);
            DrawAmbientOclusion(renderWindow, t,vertexArray);
        }
    }
    else{
        sf::Vector2f pos= GetPosition();
        vertexArray.append(sf::Vertex(sf::Vector2f(pos.x,pos.y), sf::Color::Black));
        vertexArray.append(sf::Vertex(sf::Vector2f(pos.x+Chunk::TILE_SIZE,pos.y), sf::Color::Black));
        vertexArray.append(sf::Vertex(sf::Vector2f(pos.x+Chunk::TILE_SIZE,pos.y+Chunk::TILE_SIZE), sf::Color::Black));
        vertexArray.append(sf::Vertex(sf::Vector2f(pos.x,pos.y+Chunk::TILE_SIZE), sf::Color::Black));
    }
}


void Tile::Update(float elapsedTime)
{
}

void Tile::SetPosition(float x, float y)
{

	position.x=x;
	position.y=y;
}
void Tile::SetSize(float x)
{

	size.x=x;
	size.y=x;
}

sf::Vector2f Tile::GetPosition() const
{
	/*
	if(_isLoaded)
	{
		return _sprite.getPosition();
	}*/
	return position;
}

float Tile::GetHeight() const
{
	return size.y;
	//return _sprite.getTexture()->getSize().y*_sprite.getScale().y;
}

float Tile::GetWidth() const
{
	return size.x;
	//return _sprite.getTexture()->getSize().x*_sprite.getScale().x;
}



