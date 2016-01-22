#include "GameObject.h"


GameObject::GameObject()
{
	worldPosX = 0;
	worldPosY = 0;

	texWidth = 0;
	texHeight = 0;

	scaledWidth = 0;
	scaledHeight = 0;

	texID = 0;

	current_anim_row = 0;
	current_frame_num = 0;

	row_lengths.reserve(1);
	row_lengths.push_back(1);

	longest_row = 1;

	percent_width = 1.0f;
	percent_height = 1.0f;
}

void GameObject::Render(GLuint text_id)
{
	if( text_id != 0 )
    {
        //Remove any previous transformations
        glLoadIdentity();

        //Move to rendering point
		glTranslatef( worldPosX, worldPosY, 0.f );

        //Set texture ID
        glBindTexture( GL_TEXTURE_2D, text_id );

        //Render textured quad
        glBegin( GL_QUADS );

		// TODO: Render with camera translation/rotation - Shawn, Park
		// Flip vertically for png:
            glTexCoord2f( percent_width * current_frame_num, percent_height * current_anim_row );             glVertex2f( 0.f        , scaledHeight );
            glTexCoord2f( percent_width * (current_frame_num + 1), percent_height * current_anim_row );       glVertex2f( scaledWidth, scaledHeight );
            glTexCoord2f( percent_width * (current_frame_num + 1), percent_height * (current_anim_row + 1) ); glVertex2f( scaledWidth, 0.f );
            glTexCoord2f( percent_width * current_frame_num, percent_height * (current_anim_row + 1) );       glVertex2f( 0.f        , 0.f );
        glEnd();
    }
}

void GameObject::ProgressFrames()
{
	current_frame_num++;

	if(current_frame_num >= row_lengths[current_anim_row])
	{
		current_frame_num = 0;
	}
}
void GameObject::SetNumAnimRows(const unsigned int& rows)
{
	row_lengths.clear();

	row_lengths.reserve(rows);

	for(int i = 0; i < rows; i++)
	{
		row_lengths.push_back(1);
	}

	percent_height = 1.0f / rows;
}

void GameObject::SetAnimRowLength(const unsigned int& row_index, const unsigned int& length)
{
	if(row_index < row_lengths.size())
	{
		row_lengths[row_index] = length;

		if(length > longest_row)
		{
			longest_row = length;

			percent_width = 1.0f / length;
		}
	}
}

void GameObject::SetCurrentAnimRow(const unsigned int& row_index)
{
	if(row_index < row_lengths.size())
	{
		current_anim_row = row_index;
		current_frame_num = 0;
	}
}

void GameObject::SetCurrentAnimFrame(const unsigned int& frame_index)
{
	if(frame_index < row_lengths[current_anim_row])
		current_frame_num = frame_index;
}