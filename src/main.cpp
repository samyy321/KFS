#include "VgaBuffer.h"
#include "multiboot.h"

extern "C"
void	kmain(void)
{
	// char *str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus egestas eros ligula, eget finibus turpis suscipit id. Phasellus mattis at massa porttitor ultricies. Nunc ornare fringilla nunc, vitae porta turpis mollis ut. Suspendisse eget pharetra magna, nec eleifend mauris. Donec sed neque dolor. Fusce justo sapien, vestibulum at eleifend sit amet, ullamcorper sit amet enim. Nulla iaculis, arcu a cursus ullamcorper, libero felis rhoncus purus, ac porta diam leo ut sapien. Ut elementumipsum vel auctor dignissim. Integer quis mi ut sem pharetra ultrices sit amet vel massa. Donec pulvinar malesuada dui in feugiat. Sed eget velit molestie, tempus eros ut, molestie eros. Interdum et malesuada fames ac ante ipsum primis in faucibus. Nunc vitae rutrum felis. Quisque consectetur in ligula vel luctus.Pellentesque et tincidunt lacus. Maecenas suscipit nisi tellus, et efficitur dolor venenatis eu. Nullam at mi venenatis, tincidunt libero at, sagittis mi. Phasellus at enim dui. Nulla finibus, velit id egestas porttitor, dolor erat fermentum ante, eget convallis mi turpis et elit. Nullam interdum ipsum ac vestibulum pellentesque. Integer mi mauris, ullamcorper sed mattis et, consequat in nisi.Donec lacinia orci id justo eleifend, eu lobortis metus venenatis. Etiam vitae eleifend neque, in tincidunt turpis. Fusce neque est, tincidunt congue ultrices sit amet, condimentum quis sapien. Ut venenatis placerat urna, vitae dapibus tellus. Phasellus vulputate mattis convallis. Praesent porttitor lacus nisi, sed interdum lorem pharetra at. Maecenas non lorem non est tincidunt laoreet vitae non risus. Nunc ultricies ligula sed est tempor, at iaculis magna consequat. Morbi consectetur convallis dolor at sodales. Sed pellentesque risus a ipsum aliquet, auctor ultricies orci lobortis. Proin eget velit at arcu finibus mattis. Maecenas nunc dui, iaculis convallis dui ut, iaculis tincidunt arcu. Etiam sit amet feugiat mi. Vestibulum quis dolor eget purus gravida dictum a et nulla. Sed dictum a orci eleifend laoreet. Nullam tristique, nibh et gravida pharetra, arcu nunc dapibus nisl, a lacinia justo augue a quam. Fusce vel enim vel velit posuere sagittis et in purus. Curabitur sit amet enim varius, lacinia libero in, vestibulum tellus. Maecenas consequat tortor at orci elementum commodo. Donec semper tempus arcu eget cursus. Aenean ut ultrices tellus. In hendrerit sem sit amet velit viverra, eu ornare tellus hendrerit. Curabitur at metus ac nunc feugiat aliquam vel vitae lacus. Mauris volutpat \n\n\nconsequat tortor, id elementum diam malesuada in. Ut non laoreet enim, non dictum tortor. Aliquam erat volutpat. Mauris sit amet rutrum tellus, eget vulputate odio. Pellentesque mattis est ipsum, et semper dui sodales nec. Phasellus id commodo enim. Aliquam dictum ultrices urna at fringilla. Morbi interdum felis molestie, luctus sem eget, tristique dui. Cras porttitor odio non odio molestie mattis. Vestibulum sagittis iaculis massa, facilisis auctor magna pellentesque pretium. Aliquam non pulvinar ante. Nulla a arcu imperdiet felis laoreet fermentum a in neque. Phasellus tempor nisi nec justo suscipit, lacinia tincidunt justo pulvinar. ";

	// char *str = "\ta\taa\ta";
	char *str = "qsdf\nqsdf\n\b";
	// char *str = "\n\n\b";

extern "C"
void	kmain(t_multiboot *mboot_ptr)
{
	VgaBuffer::clear();
	VgaBuffer::putstr(str);
	// VgaBuffer::putstrColor(str, WHITE, RED);
	return;
}
