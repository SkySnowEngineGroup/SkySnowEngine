// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "GameWindow.h"

namespace SkySnow
{
	GameWindow::GameWindow()
		: IWindow(EGameWindow)
		, _EWWeight(0)
		, _EWHeight(0)
		, _OSWindow(nullptr)
		, _Viewport(nullptr)
	{

	}

	GameWindow::~GameWindow()
	{
		if (_OSWindow)
		{
			delete _OSWindow;
			_OSWindow = nullptr;
		}
		if (_Viewport)
		{
			delete _Viewport;
			_Viewport = nullptr;
		}
	}

	OSWindow* GameWindow::GetOSWindow()
	{
		return _OSWindow;
	}

	Viewport* GameWindow::GetViewport()
	{
		return _Viewport;
	}
}